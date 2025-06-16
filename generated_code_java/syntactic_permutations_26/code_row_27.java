import java.util.List;
public class Sales {
    private List<Integer> monthlySales = new ArrayList<>();

    public void setMonthlySales(List<Integer> monthlySales) {
        this.monthlySales = monthlySales;
    }

    public int getQuarterlySales() {
        return monthlySales.get(0) + monthlySales.get(1) + monthlySales.get(2);
    }
}