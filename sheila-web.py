import gradio as gr
import pandas as pd
import altair as alt

# Carregar os dados do arquivo CSV
data = pd.read_csv('dados.csv', parse_dates=['Data e Hora'])

def plot_all_parameters(selected_hour=0):
    # Filtrar os dados com base no horário selecionado
    filtered_data = data[data['Data e Hora'].dt.hour == selected_hour]

    if filtered_data.empty:
        return [None, None, None, None]  # Retorna None para todos os gráficos se não houver dados para o horário selecionado

    # Lista para armazenar os gráficos
    charts = []

    # Lista de parâmetros
    parameters = ['Concentração de CO', 'Concentração de CO2', 'Umidade (%)', 'Temperatura (°C)']

    for parameter_name in parameters:
        # Filtrar os dados para o parâmetro específico
        parameter_data = filtered_data[['Data e Hora', parameter_name]]

        # Plotar os dados com Altair
        chart = alt.Chart(parameter_data).mark_line().encode(
            x='Data e Hora:T',
            y=alt.Y(f'{parameter_name}:Q', title=parameter_name),
            tooltip=['Data e Hora:T', alt.Tooltip(f'{parameter_name}:Q', title=parameter_name)]
        ).properties(
            width=400,
            height=300,
            title=f'{parameter_name} às {selected_hour}:00'
        )

        # Adicionar linha vermelha indicando limite preocupante
        if parameter_name == 'Concentração de CO':
            chart = chart + alt.Chart(pd.DataFrame({'y': [9]})).mark_rule(color='red', strokeWidth=2).encode(y='y:Q')
        elif parameter_name == 'Concentração de CO2':
            chart = chart + alt.Chart(pd.DataFrame({'y': [1000]})).mark_rule(color='red', strokeWidth=2).encode(y='y:Q')
        elif parameter_name == 'Umidade (%)':
            chart = chart + alt.Chart(pd.DataFrame({'y': [40]})).mark_rule(color='red', strokeWidth=2).encode(y='y:Q')

        charts.append(chart)

    return charts  # Retorna a lista de gráficos

# Criar a interface Gradio com quatro saídas
iface = gr.Interface(
    fn=plot_all_parameters,
    inputs=gr.Slider(minimum=0, maximum=23, step=1, label="Selecione a hora:"),
    outputs=["plot", "plot", "plot", "plot"],
    title="Gráficos de Parâmetros por Hora",
    description="Escolha a hora para visualizar os gráficos de diferentes parâmetros."
)

# Executar a interface
iface.launch(auth=('tvboxuea', '1234'))
