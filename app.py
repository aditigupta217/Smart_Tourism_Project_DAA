from flask import Flask, render_template, request, jsonify
import subprocess
import os

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/plan', methods=['POST'])
def plan_trip():
    data = request.json
    budget = data.get('budget', 0)
    city_index = data.get('cityIndex', 0)

    # Path to the compiled C executable
    executable = './knapsack'
    if os.name == 'nt':  # For Windows users
        executable = 'knapsack.exe'

    try:
        # Run the C program using subprocess
        # Pass city_index and budget as arguments
        result = subprocess.run([executable, str(city_index), str(budget)], 
                               capture_output=True, text=True, check=True)
        
        output = result.stdout
        print("C Program Output:", output) # For debugging

        # Parse the output from the C program
        lines = output.split('\n')
        places = []
        total_cost = 0
        total_rating = 0
        
        parsing_results = False
        best_route = ""
        for line in lines:
            if '---RESULT---' in line:
                parsing_results = True
                continue
            if not parsing_results:
                continue
                
            if 'PLACE:' in line:
                parts = line.split('|')
                name = parts[0].replace('PLACE:', '').strip()
                cost = int(parts[1].replace('COST:', '').strip())
                rating = int(parts[2].replace('RATING:', '').strip())
                places.append({
                    'name': name,
                    'cost': cost,
                    'rating': rating
                })
            elif 'TOTAL_COST:' in line:
                total_cost = int(line.replace('TOTAL_COST:', '').strip())
            elif 'TOTAL_RATING:' in line:
                total_rating = int(line.replace('TOTAL_RATING:', '').strip())
            elif 'ROUTE:' in line:
                best_route = line.replace('ROUTE:', '').strip()

        return jsonify({
            'status': 'success',
            'places': places,
            'totalCost': total_cost,
            'totalRating': total_rating,
            'remainingBudget': int(budget) - total_cost,
            'bestRoute': best_route
        })

    except Exception as e:
        return jsonify({
            'status': 'error',
            'message': str(e)
        }), 500

if __name__ == '__main__':
    app.run(debug=True, port=5001)
