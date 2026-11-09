
import argparse
import json
import sys

# Analitza les dades d'un servei i determina el seu estat.
def analitzar_fila(fila):
    try:
        nom = fila["nom"].strip()
        cpu = float(fila["cpu_pct"])
        memoria = float(fila["memoria_pct"])
        estat = fila["estat"].strip().lower()

    # Detecta errors o dades que falten al registre.
    except (AttributeError, TypeError, ValueError, KeyError):
        return "invalid"

    # Comprova que les dades siguin vàlides.
    if nom == "" or estat not in ("actiu", "inactiu") or cpu < 0 or cpu > 100 or memoria < 0 or memoria > 100:
        return "invalid"
    # Classifica el servei segons els nivells de consum.
    elif cpu >= 90 or memoria >= 90:
        return "critic"
    elif cpu >= 75 or memoria >= 75:
        return "avis"
    else:
        return "estable"


# Configura els arguments que es poden passar al programa.
parser = argparse.ArgumentParser(description="Auditoria del servidor")
parser.add_argument("--fitxer", required=True)
args = parser.parse_args()

# Inicialitza els comptadors dels resultats.
llegits = 0
invalids = 0
critics = 0
avisos = 0
estables = 0


try:
    # Obre el fitxer JSON i llegeix els serveis.
    with open(args.fitxer, encoding="utf-8") as fitxer:
        serveis = json.load(fitxer)

        # Analitza cada servei i actualitza els comptadors.
        for fila in serveis:
            llegits += 1
            resultat = analitzar_fila(fila)

            if resultat == "invalid":
                invalids += 1
            elif resultat == "critic":
                critics += 1
            elif resultat == "avis":
                avisos += 1
            else:
                estables += 1

# Gestiona els errors relacionats amb la lectura del fitxer.
except FileNotFoundError:
    print("ERROR: fitxer inexistent o il·legible")
    sys.exit(1)

# Gestiona els errors del format JSON.
except json.JSONDecodeError:
    print("ERROR: format JSON incorrecte")
    sys.exit(1)


# Guarda els resultats de l'auditoria en un diccionari.
informe = {
    "serveis_totals_llegits": llegits,
    "serveis_valids_analitzats": llegits - invalids,
    "serveis_critics": critics,
    "serveis_avis": avisos,
    "serveis_estables": estables,
    "registres_invalids": invalids
}

# Escriu l'informe en un fitxer JSON.
with open("informe_salut.json", "w", encoding="utf-8") as sortida:
    json.dump(informe, sortida, ensure_ascii=False, indent=4)


# Mostra el resum de l'auditoria per pantalla.
print(
    "Informe de salut generat correctament a 'informe_salut.json'.\n"
    f"Serveis totals llegits: {llegits}\n"
    f"Serveis vàlids analitzats: {llegits - invalids}\n"
    f"Serveis en estat CRÍTIC: {critics}\n"
    f"Serveis en estat AVÍS: {avisos}\n"
    f"Serveis ESTABLES: {estables}\n"
    f"Registres invàlids descartats: {invalids}"
)
