import java.lang.Math;
    public class HelloWorld {
        public static void main(String[] args) {
            float num1 = (float)(Math.random() * 10);
            float num2 = (float)(Math.random() * 10);
            float num3 = (float)(Math.random() * 10);
            String result = "" + num1 + " " + num2 + " " + num3;
            System.out.println(result);
        }
    }