public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        
        String[] id_sequence = {"ABCD", "DEFG", "HIJK"};
        
        System.out.print("Enter an index value: ");
        int index = scan.nextInt();
        
        if (index < 0 || index >= id_sequence.length) {
            System.out.println("Invalid index");
        } else {
            String result = id_sequence[index];
            System.out.println(result);
        }
    }