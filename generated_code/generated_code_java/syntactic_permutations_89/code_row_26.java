import java.util.*;

public class Solution {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int testCases = scanner.nextInt();
        List<Integer> prices = new ArrayList<>();
        for (int i = 0; i < testCases; ++i) {
            prices.add(scanner.nextInt());
        }
        int requests = scanner.nextInt();
        for (int i = 0; i < requests; ++i) {
            String code = scanner.next();
            System.out.println(prices.get(code.charAt(1) - 'A'));
        }
    }
}