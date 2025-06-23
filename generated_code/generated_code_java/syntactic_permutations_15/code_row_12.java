public static int getIndexValue(int[] id_sequence){
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter a valid index");
        int index = sc.nextInt();
        return id_sequence[index];
    }