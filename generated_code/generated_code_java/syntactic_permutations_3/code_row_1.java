public static String Hello(String Destination, String Source){
        int i = 0;
        while(i<Source.length()){
            Destination += Source[i];
            i++;
        }
        return Destination;
    }