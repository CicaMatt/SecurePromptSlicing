public class Main {
    public static void main(String[] args) {
        int num1 = (int)(Math.random()*990+10);
        int num2 = (int)(Math.random()*990+10);
        int diff = Math.abs(num1 - num2);
        System.out.println("Random numbers: "+num1+" and "+num2);
        System.out.println("Difference: "+diff);
    }
}