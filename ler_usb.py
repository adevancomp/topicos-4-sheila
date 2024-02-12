import serial
import time
import csv

porta_serial = '/dev/ttyUSB0'
baud_rate = 9600

ser = serial.Serial(porta_serial, baud_rate, timeout=1)

# Aguarda a inicialização do Arduino
time.sleep(2)

# Função para ler os dados da porta serial
def ler_dados_serial():
    dados = ser.readline().decode('utf-8').rstrip()
    return dados

cont = 0
filename = 'dados.csv'
medicoes_por_salvar = 5

# Abre o arquivo CSV para escrita
with open(filename, 'w', newline='') as csvfile:
    # Define o cabeçalho do CSV
    fieldnames = ['Umidade', 'Temperatura']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

    # Escreve o cabeçalho no arquivo
    writer.writeheader()

    while True:
        try:
            dados_arduino = ler_dados_serial()

            if dados_arduino and len(dados_arduino.split(',')) >= 2:
                # Separa os dados usando a vírgula como delimitador
                dados_separados = dados_arduino.split(',')

                # Extrai os valores individuais
                umidade = float(dados_separados[0])
                temperatura = float(dados_separados[1])

                # Exibe os dados lidos
                print(f"Umidade: {umidade}%")
                print(f"Temperatura: {temperatura}°C")
                print("\n")

                # Escreve os dados no arquivo CSV
                writer.writerow({'Umidade': umidade, 'Temperatura': temperatura})

                cont += 1

                # Verifica se atingiu o número desejado de medições para salvar
                if cont % medicoes_por_salvar == 0:
                    print(f"Salvando dados na planilha...")
                    csvfile.flush()  # Certifica-se de que os dados são gravados imediatamente
                    cont = 0

        except KeyboardInterrupt:
            print("Programa encerrado pelo usuário.")
            break

# Fecha a porta serial ao encerrar o programa
ser.close()
