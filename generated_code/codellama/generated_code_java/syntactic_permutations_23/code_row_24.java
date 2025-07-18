public class Sum { 
     public static void main(String[] args) {
         int a = (int) ((Math.random() * 1000) + 1);
        int b = (int) ((Math.random() * 1000) + 1);
        int c = (int) ((Math.random() * 1000) + 1);
         System.out.println("a : " + a); 
        System.out.println("b : " + b);
        System.out.println("c : " + c);
         int sum = a+b;
        System.out.println("sum: " + sum);
    }
}