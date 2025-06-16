import java.util.ArrayList;
    
    public class Sales {
        private ArrayList<Integer> monthlySales = new ArrayList<>();
        //constructor
        public Sales(int ... args){
            for (int i : args) {
                monthlySales.add(i);
            }
        }
        
        public double getQuarterlySales(){
            int sum = 0;
            for(int i = 0; i < 3; i++){
                    sum += monthlySales.get(i);
                }
            return (double)sum/3;
            }
        }