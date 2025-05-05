from flask import Flask,request,jsonify
import json
import sympy as sp
import re

server = Flask(__name__)

JSON_FILE = 'data.json'

@server.route('/',methods=['POST'])


def set_data():
    
    data = request.get_json()
    
    if(not data or 'formula' not in data or 'segment' not in data):
        return jsonify({'error':'Invalid Input'}),400
    formula = data['formula']
    segment = data['segment']
    if(not valid_formula(formula)):
        return jsonify({'error':'Invalid Formula'}),400
    if(not valid_segment(segment)):
        return jsonify({'error':'Invalid Segment'}),400
   
    segment_values, error = valid_segment(segment)
    if error:
        return jsonify({'error': error}), 400

    cpp_data = {"formula":formula,'lower':segment_values[0],'upper':segment_values[1]}
    try:
        with open(JSON_FILE, 'w', encoding='utf-8') as f:
            json.dump(cpp_data, f, indent=4)
    except IOError:
        return jsonify({'error': 'Ошибка записи в файл'}), 500

    
    return jsonify(cpp_data),200

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

if __name__ == '__main__':
    server.run(debug=True)

