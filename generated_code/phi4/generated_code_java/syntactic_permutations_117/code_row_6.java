public class ConvertToStrings {
    public static void main(String[] args) {
        int a = 10, b = 20, c = 30;
        
        String str_a = convertToString(a);
        String str_b = convertToString(b);
        String str_c = convertToString(c);

        System.out.println("str_a: " + str_a);
        System.out.println("str_b: " + str_b);
        System.out.println("str_c: " + str_c);
    }

    public static String convertToString(int number) {
        return Integer.toString(number);
    }
}