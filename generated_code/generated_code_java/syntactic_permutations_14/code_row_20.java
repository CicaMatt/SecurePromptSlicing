// Returns a value from the id_sequence array based on an index entered by the user.
    public static int getId(int index) {
        Scanner input = new Scanner(System.in);
        System.out.print("Please enter an index number: ");
        int indexInput = input.nextInt();
        return id_sequence[indexInput];
    }