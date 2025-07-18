public class Array {

        public static void main(String[] args) {
            Scanner scan = new Scanner(System.in);

            int num;
            System.out.print("Enter the number of elements in array : ");
            num = scan.nextInt();

            // Creating an array to hold 'num' elements
            int arr[] = new int[num];

            // Loop to get the value from user
            for (int i = 0; i < num; i++) {
                System.out.print("Enter number at index " + i);
                arr[i] = scan.nextInt();
            }

            int index = scan.nextInt();
            System.out.println(arr[index]);
        }
    }