from flask import Flask, render_template, jsonify, request
import sqlite3
import sys

#importando las librerias para server dash+flask
import dash
import dash_html_components as html
import dash_core_components as dcc
import dash_bootstrap_components as dbc
import plotly.graph_objects as go
from dash.dependencies import Input, Output

#importando las librerias para trabajar con los datos y los modelos
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


@server.route('/sensor_send_data', methods=['POST'])
def sensor_send():
    values = request.data
    print(values)
    a=str(request.values.get('id'))
    print(a.split(";")[0])
    print(a.split(";")[1].split("=")[1])
    print(a.split(";")[2].split("=")[1])
    print(a.split(";")[3].split("=")[1])
    con = sqlite3.connect(db_path)
    cur = con.cursor()
    cur.execute("INSERT INTO data VALUES(" + a.split(";")[0] + "," + "datetime('now')," + a.split(";")[1].split("=")[1] + "," + a.split(";")[3].split("=")[1] + "," + a.split(";")[2].split("=")[1] + ")")
    con.commit()
    con.close()
    return "ok",201

db_Data = './Data.db'

sensorID = []
sensorTime = []
sensorTemp = []
sensorHum = []
sensorLuz = []
con = sqlite3.connect(db_Data)
curs = con.cursor()
for fila in curs.execute("SELECT * FROM data"):
    sensorID.append(fila[0])
    sensorTime.append(fila[1])
    sensorTemp.append(fila[2])
    sensorHum.append(fila[3])
    sensorLuz.append(fila[4])
con.close()
leyenda = 'Variables del cultivo'
Temperatura = sensorTemp
Humedad = sensorHum
Luz = sensorLuz
ID = sensorID

server = Flask(__name__)
app = dash.Dash(__name__,server=server)

app.layout = html.Div(children=[
    html.H1(children = 'Grafica Temperatura'),
    dcc.Graph(id='example',
        figure={
            'data':[
                {'x': sensorTime, 'y': Temperatura, 'type': 'line', 'name': 'Temperatura'},
            ],
            'layout':{
                'title': 'Basic Dash Example'
            }
        }
    ),
    html.H1(children = 'Grafica Humedad'),
    dcc.Graph(id='example2',
        figure={
            'data':[
                {'x': sensorTime, 'y': Humedad, 'type': 'line', 'name': 'Humedad'},
            ],
            'layout':{
                'title': 'Basic Dash Example'
            }
        }
    ),
    html.H1(children = 'Grafica Luz'),
    dcc.Graph(id='example3',
        figure={
            'data':[
                {'x': sensorTime, 'y': Luz, 'type': 'line', 'name': 'Luz'},
            ],
            'layout':{
                'title': 'Basic Dash Example'
            }
        }
    )
])

@server.route('/')
def home():
    return render_template('index.html')
@server.route('/registro')
def registro():
    return render_template('registro.html')

@server.route("/visualizacion")
def captura():
    return render_template('chart.html', server.app)


@server.route('/sensor_send_data', methods=['POST'])
def sensor_send():
    values = request.data
    print(values)
    a=str(request.values.get('id'))
    print(a.split(";")[0])
    print(a.split(";")[1].split("=")[1])
    print(a.split(";")[2].split("=")[1])
    print(a.split(";")[3].split("=")[1])
    con = sqlite3.connect(db_path)
    cur = con.cursor()
    cur.execute("INSERT INTO data VALUES(" + a.split(";")[0] + "," + "datetime('now')," + a.split(";")[1].split("=")[1] + "," + a.split(";")[3].split("=")[1] + "," + a.split(";")[2].split("=")[1] + ")")
    con.commit()
    con.close()
    return "ok",201

if __name__ == '__main__':
        app.run(debug=True,host='0.0.0.0',port=80)