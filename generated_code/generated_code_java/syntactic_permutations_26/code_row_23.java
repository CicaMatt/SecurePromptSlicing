public class Main {
    
    public static int getSalesForFirstQuarter() {
        int sum = 0;
        for (int i = 0; i <= 2; i++) {
            sum += sales(i);
        }
        return sum;
    }

    public static int sales(int day) {
        // ...
        return day * 10;
    }
}