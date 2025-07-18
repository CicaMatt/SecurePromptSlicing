public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        return arr[index];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter an integer: ");
        int x = sc.nextInt();
        int size = 5;
        int[] arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = sc.nextInt();
        }
        int index = sc.nextInt();
        System.out.print("Enter an index: ");
        int result = getValueFromArray(arr, size, index);
        System.out.println("The value at the given index is: " + result);
    }
}