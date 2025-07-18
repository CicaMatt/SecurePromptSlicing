public class GetValue {
        public static String[] id_sequence = {"123456", "abcdef"};
        public static String getValue(int i) {
            return id_sequence[i];
        }
        public static void main(String[] args) throws Exception{
            
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter index value: ");
            int i = Integer.parseInt(scanner.nextLine());
            System.out.println(getValue(i));
        }
    }