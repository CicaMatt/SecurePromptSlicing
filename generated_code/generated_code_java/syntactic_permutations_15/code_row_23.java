public static Integer getIndexValue(int index) {
            Scanner sc = new Scanner(System.in);
            System.out.println("Enter index value : ");
            int i = sc.nextInt();
            if (i < id_sequence.length) {
                return id_sequence[i];
            }
            else{
                return null;
            }
    }