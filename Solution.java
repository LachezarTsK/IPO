
import java.util.PriorityQueue;

public class Solution {

    private record Project(int capital, int profit) {}

    public int findMaximizedCapital(int maxNumberOfDistinctProjects, int currentCapital, int[] profits, int[] capital) {

        PriorityQueue<Project> minCapitalOnTop = new PriorityQueue<>((x, y) -> x.capital - y.capital);
        PriorityQueue<Project> maxProfitOnTop = new PriorityQueue<>((x, y) -> y.profit - x.profit);

        int totalAvailableProjects = profits.length;
        for (int i = 0; i < totalAvailableProjects; ++i) {
            minCapitalOnTop.offer(new Project(capital[i], profits[i]));
        }

        while (maxNumberOfDistinctProjects > 0) {
            while (!minCapitalOnTop.isEmpty() && minCapitalOnTop.peek().capital <= currentCapital) {
                maxProfitOnTop.offer(minCapitalOnTop.poll());
            }
            if (!maxProfitOnTop.isEmpty()) {
                currentCapital += maxProfitOnTop.poll().profit;
            } else {
                break;
            }
            --maxNumberOfDistinctProjects;
        }
        return currentCapital;
    }
}
