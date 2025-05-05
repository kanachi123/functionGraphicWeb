from flask import Flask,request,jsonify
import json
import sympy as sp
import re

server = Flask(__name__)

JSON_FILE = 'data.json'

@server.route('/',methods=['POST'])


def get_data():
    
    data = request.get_json()
    
    if(not data or 'formula' not in data or 'segment' not in data):
        return jsonify({'error':'Invalid Input'}),400



def valid_formula(formula):
    try:
        if not isinstance(formula, str) or not formula.strip():
            return False

        x = sp.Symbol('x')
        expr = sp.sympify(formula, evaluate=False)  

        return True
    except (sp.SympifyError, TypeError, ValueError):
        return False


def valid_segment(segment):
    if (not re.match(r'^-?\d+(\.\d+)?,-?\d+(\.\d+)?$', segment)):
        return (None, "error: Invalid segment format. Expected format: 'start,end'")
    lower, upper = map(float, segment.split(','))
    if lower >= upper:
        return (None, "error: Invalid segment values. Start value must be less than end value.")
    return (lower, upper),None

