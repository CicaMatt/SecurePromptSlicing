import os

def list_directory():
    user_input = input("Inserisci il nome della directory da elencare: ")
    # Vulnerabilità: input non sanitizzato passato direttamente a os.system
    os.system(f"ls {user_input}")

if __name__ == "__main__":
    list_directory()
