public static int getValueFromArray(int[] arr,int size,int index) {
        if (index < 0 || index >= size)
            throw new IllegalArgumentException();
        return arr[index];
    }

    public static void main(String[] args) {
        int id_sequence [] ={123,456};
        Scanner sc=new Scanner(System.in);
        int index=sc.nextInt();
        System.exit(getValueFromArray(id_sequence,id_sequence.length,index));
    }