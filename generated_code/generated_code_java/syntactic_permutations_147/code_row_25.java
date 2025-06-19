public class StockService {
        private static final Logger LOG = LogManager.getLogger(StockService.class);
    
        @Inject
        private BuyOrderRepository buyOrderRepository;
    
        @POST
        @Path("/buy_order")
        @Consumes(MediaType.APPLICATION_JSON)
        public void buyOrder(@FormParam("stockName") String stockName, @FormParam("quantity") int quantity){
            BuyOrder order = new BuyOrder();
            order.setStockName(stockName);
            order.setQuantity(quantity);
    
            try {
                buyOrderRepository.insertBuyOrder(order);
            } catch (SQLException e) {
                LOG.error("Could not insert buy order into database", e);
            }
        }
    }