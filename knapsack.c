#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SELECTED 15
#define INF 1e9

// Structure to represent a tourist place
typedef struct {
  char name[100];
  int cost;
  int rating; // Value for Knapsack
  double x;   // X coordinate for TSP
  double y;   // Y coordinate for TSP
} Place;

// Function to find maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

// Function to calculate Euclidean distance
double get_distance(Place p1, Place p2) {
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// TSP Solver using Dynamic Programming (Held-Karp)
void solve_tsp(Place selected[], int n) {
  if (n <= 1) {
    if (n == 1) {
      printf("ROUTE: %s\n", selected[0].name);
    }
    return;
  }

  double dist[MAX_SELECTED][MAX_SELECTED];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      dist[i][j] = get_distance(selected[i], selected[j]);
    }
  }

  double dp[1 << MAX_SELECTED][MAX_SELECTED];
  int parent[1 << MAX_SELECTED][MAX_SELECTED];

  for (int i = 0; i < (1 << n); i++) {
    for (int j = 0; j < n; j++) {
      dp[i][j] = INF;
      parent[i][j] = -1;
    }
  }

  // Starting from the first selected place
  dp[1][0] = 0;

  for (int mask = 1; mask < (1 << n); mask++) {
    for (int u = 0; u < n; u++) {
      if (!(mask & (1 << u)))
        continue;
      if (dp[mask][u] == INF)
        continue;

      for (int v = 0; v < n; v++) {
        if (mask & (1 << v))
          continue;

        double new_dist = dp[mask][u] + dist[u][v];
        if (new_dist < dp[mask | (1 << v)][v]) {
          dp[mask | (1 << v)][v] = new_dist;
          parent[mask | (1 << v)][v] = u;
        }
      }
    }
  }

  // Find the best end point (min cost to visit all)
  double min_total = INF;
  int last = -1;
  int full_mask = (1 << n) - 1;

  for (int i = 0; i < n; i++) {
    if (dp[full_mask][i] < min_total) {
      min_total = dp[full_mask][i];
      last = i;
    }
  }

  // Reconstruct path
  int path[MAX_SELECTED];
  int curr_mask = full_mask;
  for (int i = n - 1; i >= 0; i--) {
    path[i] = last;
    int prev = parent[curr_mask][last];
    curr_mask ^= (1 << last);
    last = prev;
  }

  printf("ROUTE: ");
  for (int i = 0; i < n; i++) {
    printf("%s%s", selected[path[i]].name, (i == n - 1) ? "" : " -> ");
  }
  printf("\n");
}

// 0/1 Knapsack Implementation
void solve_knapsack(Place places[], int n, int budget) {
  int i, w;
  int **dp = (int **)malloc((n + 1) * sizeof(int *));
  for (i = 0; i <= n; i++) {
    dp[i] = (int *)malloc((budget + 1) * sizeof(int));
  }

  for (i = 0; i <= n; i++) {
    for (w = 0; w <= budget; w++) {
      if (i == 0 || w == 0) {
        dp[i][w] = 0;
      } else if (places[i - 1].cost <= w) {
        dp[i][w] = max(places[i - 1].rating + dp[i - 1][w - places[i - 1].cost],
                       dp[i - 1][w]);
      } else {
        dp[i][w] = dp[i - 1][w];
      }
    }
  }

  int res = dp[n][budget];
  int totalCost = 0;
  int totalRating = res;

  Place selected[MAX_SELECTED];
  int selected_count = 0;

  printf("---RESULT---\n");

  int temp_w = budget;
  for (i = n; i > 0 && res > 0; i--) {
    if (res == dp[i - 1][temp_w])
      continue;
    else {
      printf("PLACE: %s | COST: %d | RATING: %d\n", places[i - 1].name,
             places[i - 1].cost, places[i - 1].rating);
      if (selected_count < MAX_SELECTED) {
        selected[selected_count++] = places[i - 1];
      }
      totalCost += places[i - 1].cost;
      res -= places[i - 1].rating;
      temp_w -= places[i - 1].cost;
    }
  }

  printf("TOTAL_COST: %d\n", totalCost);
  printf("TOTAL_RATING: %d\n", totalRating);

  // Solve TSP for the selected places
  solve_tsp(selected, selected_count);

  for (i = 0; i <= n; i++)
    free(dp[i]);
  free(dp);
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s <city_index> <budget>\n", argv[0]);
    return 1;
  }

  int city_index = atoi(argv[1]);
  int budget = atoi(argv[2]);

  // Data with mock coordinates (x, y)
  Place delhi[] = {{"Red Fort", 500, 9, 10, 20},
                   {"Qutub Minar", 600, 8, 40, 50},
                   {"India Gate", 100, 10, 30, 30},
                   {"Lotus Temple", 200, 9, 50, 40},
                   {"Akshardham Temple", 800, 10, 70, 20},
                   {"Humayun's Tomb", 500, 8, 35, 25},
                   {"Chandni Chowk Food Tour", 1200, 10, 10, 25},
                   {"National Museum", 300, 7, 25, 30},
                   {"Jantar Mantar", 400, 7, 28, 28},
                   {"Waste to Wonder Park", 600, 8, 80, 40}};

  Place mumbai[] = {{"Gateway of India", 200, 10, 10, 10},
                    {"Marine Drive", 0, 10, 10, 20},
                    {"Elephanta Caves", 1000, 9, 30, 10},
                    {"Siddhivinayak Temple", 100, 9, 10, 50},
                    {"Juhu Beach", 300, 8, 10, 70},
                    {"Colaba Causeway Shopping", 1500, 9, 12, 12},
                    {"Film City Tour", 2500, 10, 40, 80},
                    {"Haji Ali Dargah", 100, 8, 10, 40},
                    {"Nehru Planetarium", 300, 7, 12, 45},
                    {"Chhatrapati Shivaji Terminus", 0, 9, 15, 15}};

  Place jaipur[] = {{"Hawa Mahal", 400, 9, 20, 20},
                    {"Amer Fort", 1000, 10, 10, 50},
                    {"City Palace", 700, 9, 20, 25},
                    {"Jantar Mantar", 500, 8, 22, 25},
                    {"Nahargarh Fort", 600, 9, 15, 45},
                    {"Chokhi Dhani", 1800, 10, 60, 10},
                    {"Jaigarh Fort", 500, 8, 12, 52},
                    {"Albert Hall Museum", 300, 7, 25, 15},
                    {"Birla Mandir", 0, 8, 30, 10},
                    {"Galta Ji Temple", 200, 9, 40, 25}};

  Place goa[] = {{"Baga Beach", 500, 9, 10, 50},
                 {"Basilica of Bom Jesus", 200, 10, 30, 30},
                 {"Dudhsagar Falls", 2500, 10, 70, 20},
                 {"Fort Aguada", 300, 8, 10, 40},
                 {"Palolem Beach", 600, 9, 20, 10},
                 {"Anjuna Flea Market", 1000, 8, 12, 55},
                 {"Scuba Diving", 4500, 10, 40, 10},
                 {"Casino Night", 3000, 9, 25, 35},
                 {"Chapora Fort", 0, 8, 15, 60},
                 {"Spice Plantation Tour", 1200, 9, 50, 25}};

  Place kerala[] = {{"Alleppey Houseboat", 5000, 10, 20, 20},
                    {"Munnar Tea Gardens", 800, 10, 40, 50},
                    {"Athirappilly Falls", 500, 9, 30, 60},
                    {"Wayanad Safari", 2000, 9, 10, 90},
                    {"Varkala Beach", 400, 8, 20, 10},
                    {"Padmanabhaswamy Temple", 200, 9, 25, 5},
                    {"Thekkady Elephant Ride", 1500, 8, 60, 40},
                    {"Kochi Fort Walk", 300, 8, 15, 30},
                    {"Periyar Boat Ride", 1200, 9, 62, 42},
                    {"Bekal Fort", 400, 7, 5, 95}};

  Place bangalore[] = {{"Lalbagh Botanical Garden", 100, 9, 30, 30},
                       {"Bangalore Palace", 500, 10, 30, 50},
                       {"Bannerghatta Zoo Safari", 1200, 10, 40, 10},
                       {"Cubbon Park", 0, 8, 32, 40},
                       {"ISKCON Temple", 100, 9, 10, 60},
                       {"Wonderla Amusement Park", 2500, 10, 5, 20},
                       {"Commercial Street Shopping", 2000, 9, 40, 45},
                       {"Nandi Hills Trip", 1500, 8, 35, 95},
                       {"Visvesvaraya Museum", 100, 7, 33, 42},
                       {"Brigade Road Walk", 0, 8, 38, 40}};

  Place hyderabad[] = {{"Charminar", 100, 10, 20, 20},
                       {"Golconda Fort", 300, 10, 10, 30},
                       {"Ramoji Film City", 3000, 10, 80, 20},
                       {"Salar Jung Museum", 200, 9, 22, 22},
                       {"Hussain Sagar Lake", 200, 8, 30, 40},
                       {"Birla Mandir", 0, 9, 28, 38},
                       {"Chowmahalla Palace", 200, 9, 18, 18},
                       {"Nehru Zoological Park", 100, 8, 10, 10},
                       {"Snow World", 800, 8, 32, 42},
                       {"Laad Bazaar Shopping", 1500, 9, 19, 19}};

  Place varanasi[] = {{"Kashi Vishwanath Temple", 200, 10, 20, 20},
                      {"Ganga Aarti at Dashashwamedh", 100, 10, 22, 18},
                      {"Sarnath Trip", 500, 9, 40, 40},
                      {"Assi Ghat Boat Ride", 800, 10, 25, 10},
                      {"Manikarnika Ghat Visit", 0, 8, 23, 22},
                      {"Banaras Hindu University", 0, 7, 30, 10},
                      {"Ramnagar Fort", 200, 7, 45, 15},
                      {"Sankat Mochan Temple", 0, 8, 28, 12},
                      {"Tulsi Manas Mandir", 0, 7, 27, 13},
                      {"Local Silk Saree Shopping", 5000, 10, 25, 25}};

  if (city_index == 0)
    solve_knapsack(delhi, 10, budget);
  else if (city_index == 1)
    solve_knapsack(mumbai, 10, budget);
  else if (city_index == 2)
    solve_knapsack(jaipur, 10, budget);
  else if (city_index == 3)
    solve_knapsack(goa, 10, budget);
  else if (city_index == 4)
    solve_knapsack(kerala, 10, budget);
  else if (city_index == 5)
    solve_knapsack(bangalore, 10, budget);
  else if (city_index == 6)
    solve_knapsack(hyderabad, 10, budget);
  else if (city_index == 7)
    solve_knapsack(varanasi, 10, budget);
  else
    printf("Invalid City Index\n");

  return 0;
}
