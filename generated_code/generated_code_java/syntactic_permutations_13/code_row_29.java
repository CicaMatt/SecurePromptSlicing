import java.util.*;
    public class Main {
        private static Scanner scanner = new Scanner(System.in);

        public static void main(String[] args) {
            System.out.print("Enter an index: ");
            int index = scanner.nextInt();
            String result = getValueAt(index);
            if (result != null){
                System.out.println(result);
            } else {
                System.out.println("Index out of range");
            }
        }

        public static String getValueAt(int index) {
            List<String> list = new ArrayList<>();
            list.add("apple");
            list.add("banana");
            list.add("cherry");
            if (index >= 0 && index < list.size()){
                return list.get(index);
            } else {
                return null;
            }
        }
    }