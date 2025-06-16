import java.util.ArrayList;
    class Main {
        public static int getItem(int idx) {
            ArrayList<Integer> id_sequence = new ArrayList<Integer>();
            id_sequence.add(5);
            id_sequence.add(27);
            id_sequence.add(14);
            return id_sequence.get(idx);
        }
    }