import java.util.ArrayList;
import java.util.List;
import org.springframework.data.repository.query.Param;

public class ForLoop {
    public void main(String[] args) {
        List<Integer> sales = new ArrayList<>();
        sales.add(500);
        sales.add(1000);
        sales.add(750);
        int sum=0;
        for (int i = 0; i < sales.size(); i++) {
            sum += getMonthlySales(sales.get(i));
        }
    }
    
    public static int getMonthlySales(int month) {
        return month;
    }
}