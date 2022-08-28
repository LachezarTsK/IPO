
/**
 * @param {number} maxNumberOfDistinctProjects
 * @param {number} currentCapital
 * @param {number[]} profits
 * @param {number[]} capital
 * @return {number}
 */
var findMaximizedCapital = function (maxNumberOfDistinctProjects, currentCapital, profits, capital) {

    const {PriorityQueue} = require('@datastructures-js/priority-queue');
    const minCapitalOnTop = new MinPriorityQueue({compare: (x, y) => x.capital - y.capital});
    const maxProfitOnTop = new MaxPriorityQueue({compare: (x, y) => y.profit - x.profit});

    const totalAvailableProjects = profits.length;
    for (let i = 0; i < totalAvailableProjects; ++i) {
        minCapitalOnTop.enqueue(new Project(capital[i], profits[i]));
    }

    while (maxNumberOfDistinctProjects > 0) {
        while (!minCapitalOnTop.isEmpty() && minCapitalOnTop.front().capital <= currentCapital) {
            maxProfitOnTop.enqueue(minCapitalOnTop.dequeue());
        }
        if (!maxProfitOnTop.isEmpty()) {
            currentCapital += maxProfitOnTop.dequeue().profit;
        } else {
            break;
        }
        --maxNumberOfDistinctProjects;
    }
    return currentCapital;
};

/**
 * @param {number} capital
 * @param {number} profit
 */
function Project(capital, profit) {
    this.capital = capital;
    this.profit = profit;
}
