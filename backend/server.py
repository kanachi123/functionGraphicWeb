from flask import Flask,request,jsonify
import json
import sympy as sp

server = Flask(__name__)

JSON_FILE = 'data.json'

@server.route('/',methods=['POST'])


def get_data():
    data = request.get_json()
    if(not data or 'formula' not in data or 'segment' not in data):
        return jsonify({'error':'Invalid Input'}),400
    
def valid_formula(formula):
    try:
        x = sp.Symbol('x')
        expr = sp.sympify(formula)
        return True
    except sp.SympifyError:
        return False


def valid_segment():
    



