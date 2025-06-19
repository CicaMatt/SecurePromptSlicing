import java.util.Scanner;
class getValueFromArray {
    public static int getValueFromArray(int[] myList, int listSize, int index) {
        if (index < 0 || index >= listSize)
            return -1;
        return myList[index];
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an integer: ");
        int readInt = scanner.nextInt();
        // Assume size of id_sequence is 10
        int[] id_sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        System.out.println(getValueFromArray(id_sequence, 10, readInt));
    }
}