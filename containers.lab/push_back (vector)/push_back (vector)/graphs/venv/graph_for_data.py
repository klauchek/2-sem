import pandas as pd
import plotly.graph_objects as go

data = pd.read_excel("data.xlsx", sheet_name = 'Лист1')

fig = go.Figure()

fid.add_trace(go.Scatter(
              x = data['x'],
              y = data['y'],
              name = "data",
              marker = dict(color = 'purple', size = 2)
            ))

fit.update_layout(title_text = "Graph of vector")

fig.update_xaxes(title_text = "size")
fig.update_yaxes(title_text = "capacity")

fig.show()

