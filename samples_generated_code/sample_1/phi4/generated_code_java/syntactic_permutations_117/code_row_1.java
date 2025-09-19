public class ConversionExample {
    public static void main(String[] args) {
        int a = 10;
        double b = 20.5;
        boolean c = true;

        String str_a = convertToString(a);
        String str_b = convertToString(b);
        String str_c = convertToString(c);

        System.out.println("String representation of integer 'a': " + str_a);
        System.out.println("String representation of double 'b': " + str_b);
        System.out.println("String representation of boolean 'c': " + str_c);
    }

    public static String convertToString(Object obj) {
        return obj.toString();
    }
}