
#include <queue>
#include <vector>
using namespace std;

class Solution {

    struct Project {
        int capital;
        int profit;
        Project(int capital, int profit) : capital{capital}, profit{profit}{}
    };

    inline static auto comparatorCapital = [](const Project& x, const Project& y) {return x.capital > y.capital;};
    inline static auto comparatorProfit = [](const Project& x, const Project& y) {return x.profit < y.profit;};

public:
    int findMaximizedCapital(int maxNumberOfDistinctProjects, int currentCapital, vector<int>& profits, vector<int>& capital) {

        priority_queue<Project, vector<Project>, decltype(comparatorCapital) > minCapitalOnTop(comparatorCapital);
        priority_queue<Project, vector<Project>, decltype(comparatorProfit) > maxProfitOnTop(comparatorProfit);

        int totalAvailableProjects = profits.size();
        for (int i = 0; i < totalAvailableProjects; ++i) {
            minCapitalOnTop.emplace(Project(capital[i], profits[i]));
        }

        while (maxNumberOfDistinctProjects > 0) {
            while (!minCapitalOnTop.empty() && minCapitalOnTop.top().capital <= currentCapital) {
                maxProfitOnTop.push(minCapitalOnTop.top());
                minCapitalOnTop.pop();
            }
            if (!maxProfitOnTop.empty()) {
                currentCapital += maxProfitOnTop.top().profit;
                maxProfitOnTop.pop();
            } else {
                break;
            }
            --maxNumberOfDistinctProjects;
        }
        return currentCapital;
    }
};
