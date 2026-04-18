# 🌍 Smart Tourism Budget Planner

> **Maximize your travel experiences within budget — powered by the 0/1 Knapsack Algorithm**

[![Python](https://img.shields.io/badge/Python-3.8+-3776AB?style=for-the-badge&logo=python&logoColor=white)](https://python.org)
[![Flask](https://img.shields.io/badge/Flask-2.0+-000000?style=for-the-badge&logo=flask&logoColor=white)](https://flask.palletsprojects.com)
[![C](https://img.shields.io/badge/C-Algorithm-A8B9CC?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![JavaScript](https://img.shields.io/badge/JavaScript-ES6+-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black)](https://developer.mozilla.org/en-US/docs/Web/JavaScript)
[![License: MIT](https://img.shields.io/badge/License-MIT-gold?style=for-the-badge)](LICENSE)

---

## 📸 Preview

```
┌─────────────────────────────────────────────┐
│  🌍  Smart Tourism Budget Planner           │
│  ─────────────────────────────────────────  │
│  Destination: 🗼 Paris, France              │
│  Budget: $60                                │
│                                             │
│  ✅ 7 places selected  |  $60 spent         │
│  Budget Used ████████████████████ 100%      │
│                                             │
│  [Louvre Museum]  [Notre-Dame]  [Sacré-Cœur]│
│  [Sainte-Chapelle] [Pompidou]  [Seine Tour] │
└─────────────────────────────────────────────┘
```

---

## 📖 Table of Contents

- [About the Project](#-about-the-project)
- [Tech Stack](#-tech-stack)
- [How the Algorithm Works](#-how-the-algorithm-works)
- [Project Structure](#-project-structure)
- [Getting Started](#-getting-started)
- [Cities & Places](#-cities--places)
- [API Reference](#-api-reference)
- [Features](#-features)
- [Contributing](#-contributing)
- [License](#-license)

---

## 🧭 About the Project

**Smart Tourism Budget Planner** is a full-stack web application that helps travelers select the **best combination of tourist places** to visit within a given budget. Instead of guessing which places to skip, the app uses a classic Computer Science algorithm — **0/1 Knapsack via Dynamic Programming** — to find the mathematically optimal itinerary.

Think of it as a smart travel advisor that:
- **Evaluates** all possible combinations of tourist spots
- **Selects** the set with maximum total experience rating
- **Stays** strictly within your budget
- **Visualizes** results on an interactive map

This project is also a great learning resource for students studying **Data Structures & Algorithms**, **System Programming (C)**, and **Full-Stack Web Development**.

---

## 🛠 Tech Stack

| Layer | Technology | Purpose |
|---|---|---|
| **Algorithm** | C (GCC) | 0/1 Knapsack via Dynamic Programming |
| **Backend** | Python + Flask | REST API server, subprocess bridge |
| **Frontend** | HTML + CSS + Vanilla JS | UI, animations, interactivity |
| **Map** | Leaflet.js + CartoDB | Interactive place markers & routes |
| **Fonts** | Playfair Display + DM Sans | Typography |

---

## ⚙️ How the Algorithm Works

The **0/1 Knapsack Problem** is a classic optimization problem:

> Given a set of items (tourist places), each with a **weight** (cost in USD) and a **value** (experience rating), find the subset of items that **maximizes total value** without exceeding the **weight capacity** (budget).

The `0/1` means each place is either **fully included (1)** or **excluded (0)** — you can't "half-visit" a museum.

### Dynamic Programming Approach

```
dp[i][w] = max value using first i places with budget w

For each place i and budget w:
  Option A: Skip place i  → dp[i][w] = dp[i-1][w]
  Option B: Take place i  → dp[i][w] = dp[i-1][w - cost[i]] + value[i]
  
Choose whichever option gives higher value.
```

**Time Complexity:** `O(n × W)` where n = number of places, W = budget  
**Space Complexity:** `O(n × W)`

### Data Flow

```
Browser (HTML form)
    │  POST /plan  { city: "paris", budget: 60 }
    ▼
Flask (app.py)
    │  subprocess.run(["./knapsack", "0", "60"])
    ▼
C Binary (knapsack)
    │  Builds DP table → Backtracks → Outputs JSON
    ▼
Flask
    │  Returns JSON response
    ▼
Browser (script.js)
    │  Renders cards + progress bar + Leaflet map
    ▼
User sees optimal itinerary ✅
```

---

## 📁 Project Structure

```
smart-tourism-budget-planner/
│
├── knapsack.c       # C program — 0/1 Knapsack algorithm + city data
├── app.py           # Flask backend — compiles C, exposes REST API
├── index.html       # Frontend — hero, form, results, map
├── style.css        # Styling — navy/gold travel aesthetic, animations
├── script.js        # Frontend logic — API calls, cards, Leaflet map
│
└── README.md        # You are here!
```

---

## 🚀 Getting Started

### Prerequisites

Make sure you have these installed:

- **Python 3.8+** — [Download](https://python.org/downloads)
- **GCC** (C compiler)
  - Linux/Mac: usually pre-installed (`gcc --version`)
  - Windows: install via [MinGW](https://www.mingw-w64.org/) or use WSL
- **pip** — Python package manager

### Installation

**1. Clone the repository**
```bash
git clone https://github.com/YOUR_USERNAME/smart-tourism-budget-planner.git
cd smart-tourism-budget-planner
```

**2. Install Python dependencies**
```bash
pip install flask flask-cors
```

**3. Compile the C program**
```bash
gcc -O2 -o knapsack knapsack.c
```

**4. Start the Flask server**
```bash
python app.py
```

**5. Open in browser**
```
http://localhost:5000
```

That's it! 🎉

### Quick Test (Command Line)

You can also run the C program directly to test it:

```bash
# Usage: ./knapsack <city_index> <budget>
# City indices: 0=Paris, 1=Tokyo, 2=New York, 3=Dubai, 4=Rome

./knapsack 0 60     # Paris with $60 budget
./knapsack 1 100    # Tokyo with $100 budget
./knapsack 3 150    # Dubai with $150 budget
```

---

## 🏙 Cities & Places

The app includes **5 cities** with **10 tourist places** each, predefined in `knapsack.c`:

| # | City | Country | Highlights |
|---|---|---|---|
| 0 | 🗼 Paris | France | Eiffel Tower, Louvre, Versailles |
| 1 | 🏯 Tokyo | Japan | Senso-ji, DisneySea, teamLab |
| 2 | 🗽 New York | USA | Statue of Liberty, Central Park, MoMA |
| 3 | 🌆 Dubai | UAE | Burj Khalifa, Desert Safari, Palm Jumeirah |
| 4 | 🏛️ Rome | Italy | Colosseum, Vatican, Trevi Fountain |

Each place has:
- **Cost** — entry fee in USD (free places have cost = 0)
- **Value** — experience score out of 100 (used by algorithm)
- **Rating** — display rating out of 5.0
- **Category** — Landmark / Museum / Heritage / Nature / Experience / Culture

---

## 📡 API Reference

### `POST /plan`

Plan a trip based on city and budget.

**Request Body:**
```json
{
  "city": "paris",
  "budget": 60
}
```

**Response:**
```json
{
  "city": "Paris",
  "budget": 60,
  "total_cost": 60,
  "total_value": 542,
  "remaining": 0,
  "places": [
    {
      "name": "Louvre Museum",
      "cost": 17,
      "value": 90,
      "rating": 4.8,
      "category": "Museum",
      "description": "World's largest art museum, home to the Mona Lisa"
    }
  ]
}
```

**Valid city values:** `paris`, `tokyo`, `new york`, `dubai`, `rome`

---

### `GET /cities`

Returns the list of available cities.

**Response:**
```json
{
  "cities": ["paris", "tokyo", "new york", "dubai", "rome"]
}
```

---

## ✨ Features

- 🧮 **0/1 Knapsack Algorithm** — mathematically optimal place selection
- 🗺️ **Interactive Map** — Leaflet.js with numbered markers and dotted route line
- 📊 **Budget Progress Bar** — animated visualization of spending
- 🃏 **Place Cards** — each card shows name, category, rating, cost, and score bar
- 🏷️ **Category Filter** — filter by Landmark, Museum, Heritage, Nature, etc.
- 📱 **Responsive Design** — works on mobile, tablet, and desktop
- ✨ **Smooth Animations** — staggered card reveals, shimmer effects, hover states
- 🎨 **Luxury Travel Aesthetic** — deep navy, warm gold, Playfair Display typography
- ⚡ **Fast C Backend** — algorithm runs in microseconds via subprocess

---

## 🤝 Contributing

Contributions are welcome! Here are some ideas to extend the project:

- Add more cities and tourist places in `knapsack.c`
- Add a **duration** field (time per place) and optimize for both budget + time
- Integrate a **real attractions API** (Google Places, Foursquare)
- Add **user authentication** to save past itineraries
- Deploy to **Heroku / Railway / Render**
- Add **multi-language support**

### Steps to contribute

```bash
# Fork the repo, then:
git checkout -b feature/your-feature-name
git commit -m "Add: your feature description"
git push origin feature/your-feature-name
# Open a Pull Request
```

---

## 📄 License

This project is licensed under the **MIT License** — feel free to use, modify, and distribute it.

---

## 🙏 Acknowledgements

- [Leaflet.js](https://leafletjs.com/) — open-source interactive maps
- [CartoDB](https://carto.com/) — dark map tile layer
- [Google Fonts](https://fonts.google.com/) — Playfair Display & DM Sans
- The classic **0/1 Knapsack Problem** from Algorithm Design literature

---

<div align="center">

**Made with ❤️ | Python + C + Vanilla JS**

*If this project helped you, please ⭐ star the repository!*

</div>
