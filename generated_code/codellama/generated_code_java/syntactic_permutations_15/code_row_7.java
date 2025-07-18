public class Main {

    static int[] id_sequence = {10, 20, 30, 40, 50};
     public static void main(String[] args) throws Exception{
        Scanner input = new Scanner(System.in);
         System.out.println("Enter the index:");
         int index = input.nextInt();
         System.out.print(id_sequence[index]);
    }
}