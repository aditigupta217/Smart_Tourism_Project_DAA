# 🗺️ Smart Tourism Planner

A command-line travel optimization tool written in C that helps tourists plan the **best sightseeing itinerary** within a given budget. It uses two classic algorithms — **0/1 Knapsack** for place selection and **Held-Karp TSP** for route optimization — to maximize your travel experience.

---

## 🧠 How It Works

The program solves a two-stage optimization problem:

1. **Place Selection (0/1 Knapsack):** Given a budget, it selects the set of tourist attractions that maximizes total rating while staying within cost limits.

2. **Route Optimization (TSP – Held-Karp Algorithm):** Once the best places are selected, it finds the shortest path to visit all of them using dynamic programming with bitmask states.

---

## 🏙️ Supported Cities

| Index | City       |
|-------|------------|
| 0     | Delhi      |
| 1     | Mumbai     |
| 2     | Jaipur     |
| 3     | Goa        |
| 4     | Kerala     |
| 5     | Bangalore  |
| 6     | Hyderabad  |
| 7     | Varanasi   |

Each city has **10 curated tourist places** with associated entry costs, ratings, and map coordinates.

---

## ⚙️ Compilation

Make sure you have `gcc` installed.

```bash
gcc -o smart_tourism knapsack.c -lm
```

The `-lm` flag is required to link the math library used for distance calculations.

---

## 🚀 Usage

```bash
./smart_tourism <city_index> <budget>
```

**Example** — Best places to visit in Jaipur with a budget of ₹3000:

```bash
./smart_tourism 2 3000
```

**Sample Output:**

```
---RESULT---
PLACE: Amer Fort | COST: 1000 | RATING: 10
PLACE: Nahargarh Fort | COST: 600 | RATING: 9
PLACE: Hawa Mahal | COST: 400 | RATING: 9
PLACE: Galta Ji Temple | COST: 200 | RATING: 9
PLACE: Birla Mandir | COST: 0 | RATING: 8
TOTAL_COST: 2200
TOTAL_RATING: 45
ROUTE: Birla Mandir -> Hawa Mahal -> Amer Fort -> Nahargarh Fort -> Galta Ji Temple
```

---

## 🔬 Algorithms

### 0/1 Knapsack
- Runs in **O(n × W)** time, where `n` is the number of places and `W` is the budget.
- Uses a 2D DP table to compute the maximum achievable rating.
- Backtracks through the table to identify which places were selected.

### Held-Karp TSP (Bitmask DP)
- Runs in **O(2ⁿ × n²)** time.
- Uses a bitmask to represent visited subsets of selected places.
- Finds the shortest path (by Euclidean distance) through all selected places.
- Maximum supported places: **15** (`MAX_SELECTED`).

---

## 🧩 Data Model

Each tourist place is represented as:

```c
typedef struct {
  char name[100];   // Name of the place
  int cost;         // Entry cost in ₹
  int rating;       // Attractiveness score (used as knapsack value)
  double x;         // X coordinate (for TSP distance calculation)
  double y;         // Y coordinate (for TSP distance calculation)
} Place;
```

---

## 📌 Constraints & Notes

- Maximum selectable places for TSP: **15** (due to bitmask DP memory limits).
- Coordinates are mock 2D values used to simulate real map distances.
- Budget should be a **positive integer** in Indian Rupees (₹).
- If an invalid city index is provided, the program prints `Invalid City Index`.

---


## 🛠️ Dependencies

- Standard C libraries: `stdio.h`, `stdlib.h`, `string.h`, `math.h`
- Compiler: GCC (or any C99-compatible compiler)
