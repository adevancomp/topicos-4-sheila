import serial
import time


porta_serial = '/dev/USBy0'
baud_rate = 9600  

ser = serial.Serial(porta_serial, baud_rate, timeout=1)

# Aguarda a inicialização do Arduino
time.sleep(2)

# Função para ler os dados da porta serial
def ler_dados_serial():
    dados = ser.readline().decode('utf-8').rstrip()
    return dados

while True:
    try:
        dados_arduino = ler_dados_serial()

        if dados_arduino and len(dados_arduino.split(','))>=1:
            # Separa os dados usando a vírgula como delimitador
            dados_separados = dados_arduino.split(',')

            # Extrai os valores individuais
            data_hora = dados_separados[0]
            concentracao_co = float(dados_separados[1])
            concentracao_co2 = float(dados_separados[2])
            umidade = float(dados_separados[3])
            temperatura = float(dados_separados[4])

            # Exibe os dados lidos
            print(f"Data e Hora: {data_hora}")
            print(f"Concentração de CO: {concentracao_co} ppm")
            print(f"Concentração de CO2: {concentracao_co2} ppm")
            print(f"Umidade: {umidade}%")
            print(f"Temperatura: {temperatura}°C")
            print("\n")

    except KeyboardInterrupt:
        print("Programa encerrado pelo usuário.")
        break

# Fecha a porta serial ao encerrar o programa
ser.close()
