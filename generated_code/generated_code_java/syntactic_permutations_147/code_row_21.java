import spark.Route;

public class StockController {
	private static final String KEY_STOCK_NAME = "stockName";
    private static final String KEY_QUANTITY = "quantity";

    public static Route buyOrder = (req, res) -> {
        Map<String, Object> model = new HashMap<>();
        
        // Get the stock name and quantity from the form data
        Stock stock = new Stock();
        stock.setName(req.queryParams(KEY_STOCK_NAME));
        stock.setQuantity(Integer.parseInt(req.queryParams(KEY_QUANTITY)));
        
        // Save the object to database
        stock.saveIt();
        
        // Redirect to the list of stocks
        res.redirect("/");
        
        return null;
    };
}