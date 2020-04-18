
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.JFrame;
import javax.swing.WindowConstants;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class Plotter extends JFrame {
  
    public Plotter() {
        initComponents();
    }
    
    static class Server {
        private DatagramSocket sock;
        private DatagramPacket request,resp;
        private final int port;
        private int x,y,id;
        
        public Server( int port ){
            this.port = port;
        }
        public void start(){
            try{
                sock = new DatagramSocket(port); 
                sock.setReuseAddress(true);
            }catch(Exception e){
                e.printStackTrace();
            }
        }
        public void receive(){
            try{
                byte[] buffer = new byte[65536];
                request = new DatagramPacket(buffer, buffer.length);
                sock.receive(request);
                byte[] data = request.getData();
                ByteBuffer buf = ByteBuffer.wrap(data);
                buf.order(ByteOrder.LITTLE_ENDIAN);
                this.id = buf.getInt();
                this.x = buf.getInt();
                this.y = buf.getInt();
            }catch( Exception e){
                e.printStackTrace();
            }
        }
        public void response( int idd ){
            try{
                ByteBuffer res =  ByteBuffer.allocate(20);
                res.order(ByteOrder.LITTLE_ENDIAN);
                res.putInt(idd);
                for (int i = 0 ; i < 3 ; i++)
                    res.putInt(0);
                resp = new DatagramPacket(res.array(),res.limit(),request.getAddress(),request.getPort() );
                sock.send(resp);
            }catch( Exception e){
                e.printStackTrace();
            }
        }
        public int getID(){ return this.id; }
        public int getX(){ return this.x; }
        public int getY(){ return this.y; }
    }
    
    @Override
    public void paint( Graphics g ) {
        int previous;
        int idRequest;
        boolean draw = true;
        Plotter.Server server = new Plotter.Server(7200);
        server.start();
        while(true) {
            idRequest = 0;
            previous = 300;
            setPlane(g);
            if ( draw )
                g.setColor(Color.ORANGE);
            else
                g.setColor(Color.WHITE);
            
            for( int i=0; i < 800; i++ ){
                server.receive();
                if ( idRequest < server.getID() )
                    i--;
                else{
                    idRequest++;
                    g.drawLine( i,previous,server.getX(), server.getY() );
                    previous = server.getY();
                }
                server.response(idRequest);
            }
            draw=!draw;
        }
    }
    
    private static void setPlane( Graphics g){
        g.setColor(Color.BLACK);
        g.drawLine(400,0,400,700);
        g.drawLine(0,300,900,300);
        g.setColor(Color.BLUE);
        g.drawLine(0,300,0,420);
        g.drawLine(0,420,321,168);
        g.drawLine(321,168,322,421);
        g.drawLine(321,421,641,168);
        g.drawLine(641,168,642,421);
        g.drawLine(641,421,800,300);
    }
    
    @SuppressWarnings("unchecked")                         
    private void initComponents() {

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        
        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 800, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 600, Short.MAX_VALUE)
        );
        pack();
    }                    

    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(() -> {
            Plotter gf = new Plotter();
            gf.setVisible(true);
            gf.setTitle("Servidor Gráfico");
            gf.setBackground(Color.WHITE);
            gf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        });
    }
}

