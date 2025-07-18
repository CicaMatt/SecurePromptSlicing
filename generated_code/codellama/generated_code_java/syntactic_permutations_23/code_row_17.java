java
public class Exercise1 {
    public static void main(String[] args) {
        int a = (int) (Math.random() * 1000 + 1000);
        int b = (int) (Math.random() * 1000 + 1000);
        int c = (int) (Math.random() * 1000 + 1000);
        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        int sum = (int) (a + b + c);
        int sum2 = (int) (sum * 10);
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum2);
    }
}