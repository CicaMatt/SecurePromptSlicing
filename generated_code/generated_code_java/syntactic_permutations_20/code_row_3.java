public class Offset {
    public static void main(String[] args) {
        int value = Integer.parseInt(args[0]);
        int offsetValue = value + 1000;
        System.out.println("Original value : " + value);
        System.out.println("Offset value: " + offsetValue);
    }
}