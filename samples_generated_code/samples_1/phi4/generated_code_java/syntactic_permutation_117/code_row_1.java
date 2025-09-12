public class Converter {
    public static void main(String[] args) {
        int a = 10;
        double b = 20.5;
        boolean c = true;

        String str_a = convertToString(a);
        String str_b = convertToString(b);
        String str_c = convertToString(c);

        System.out.println("String representation of a: " + str_a);
        System.out.println("String representation of b: " + str_b);
        System.out.println("String representation of c: " + str_c);
    }

    public static String convertToString(Object obj) {
        if (obj instanceof Integer || obj instanceof Double || obj instanceof Boolean) {
            return obj.toString();
        }
        throw new IllegalArgumentException("Unsupported type");
    }
}