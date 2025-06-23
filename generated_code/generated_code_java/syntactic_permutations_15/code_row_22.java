public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    System.out.println("Enter a number to print its corresponding id_sequence");
    int n = sc.nextInt();
    String[] id_sequence = {"123", "456", "789"};
    for (int i = 0; i < id_sequence.length; i++) {
        if (n == i) {
            System.out.println(id_sequence[i]);
        }
    }
}