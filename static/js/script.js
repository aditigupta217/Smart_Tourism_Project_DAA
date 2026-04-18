document.addEventListener('DOMContentLoaded', () => {
    const planBtn = document.getElementById('planBtn');
    const budgetInput = document.getElementById('budget');
    const citySelect = document.getElementById('city');
    const resultsSection = document.getElementById('results');
    const placesGrid = document.getElementById('placesGrid');
    const progressBar = document.getElementById('progressBar');
    const progressText = document.getElementById('progressText');
    const totalCostEl = document.getElementById('totalCost');
    const remainingBudgetEl = document.getElementById('remainingBudget');
    const totalRatingEl = document.getElementById('totalRating');

    planBtn.addEventListener('click', async () => {
        const budget = budgetInput.value;
        const cityIndex = citySelect.value;

        if (!budget || budget <= 0) {
            alert('Please enter a valid budget');
            return;
        }

        // Show loading state
        planBtn.disabled = true;
        planBtn.innerHTML = '<span class="btn-text">Calculating...</span> <i class="fa-solid fa-spinner fa-spin"></i>';

        try {
            const response = await fetch('/plan', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({
                    budget: parseInt(budget),
                    cityIndex: parseInt(cityIndex)
                }),
            });

            const data = await response.json();

            if (data.status === 'success') {
                displayResults(data, budget);
            } else {
                alert('Error: ' + data.message);
            }
        } catch (error) {
            console.error('Fetch error:', error);
            alert('Something went wrong. Please try again.');
        } finally {
            planBtn.disabled = false;
            planBtn.innerHTML = '<span class="btn-text">Plan My Trip</span> <i class="fa-solid fa-plane-departure"></i>';
        }
    });

    function displayResults(data, initialBudget) {
        resultsSection.classList.remove('hidden');
        
        // Update summary cards
        totalCostEl.textContent = `₹${data.totalCost}`;
        remainingBudgetEl.textContent = `₹${data.remainingBudget}`;
        totalRatingEl.textContent = data.totalRating;

        // Update progress bar
        const percentage = (data.totalCost / initialBudget) * 100;
        progressBar.style.width = `${percentage}%`;
        progressText.textContent = `${Math.round(percentage)}% used`;

        // Update Best Route (TSP)
        const routeEl = document.getElementById('bestRoute');
        routeEl.innerHTML = '';
        if (data.bestRoute) {
            const steps = data.bestRoute.split(' -> ');
            steps.forEach((step, i) => {
                const stepSpan = document.createElement('span');
                stepSpan.className = 'route-step';
                stepSpan.textContent = step;
                routeEl.appendChild(stepSpan);

                if (i < steps.length - 1) {
                    const arrow = document.createElement('i');
                    arrow.className = 'fa-solid fa-arrow-right route-arrow';
                    routeEl.appendChild(arrow);
                }
            });
        }

        // Clear and populate places grid
        placesGrid.innerHTML = '';
        data.places.forEach((place, index) => {
            const card = document.createElement('div');
            card.className = 'place-card';
            card.style.animationDelay = `${index * 0.1}s`;
            
            card.innerHTML = `
                <div class="place-card-body">
                    <h3 class="place-name">${place.name}</h3>
                    <div class="place-details">
                        <span class="place-cost">₹${place.cost}</span>
                        <span class="place-rating">
                            <i class="fa-solid fa-star"></i>
                            Rating: ${place.rating}/10
                        </span>
                    </div>
                </div>
            `;
            placesGrid.appendChild(card);
        });

        // Scroll to results
        resultsSection.scrollIntoView({ behavior: 'smooth' });
    }
});
