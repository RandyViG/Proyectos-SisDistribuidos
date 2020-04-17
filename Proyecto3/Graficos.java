import java.io.*;
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

public class Graficos extends JFrame {
  
    public Graficos() {
        initComponents();
    }
    
    static class Server {
        private DatagramSocket sock;
        private DatagramPacket reply,resp;
        private final int port;
        private int x,y,id;
        
        public Server( int port ){
            this.port = port;
        }
        public void start(){
            try{
                sock = new DatagramSocket(port); 
                sock.setReuseAddress(true);
            }catch(IOException e){
                System.err.println("IOException " + e);
            }
        }
        public void receive(){
            try{
                byte[] buffer = new byte[65536];
                reply = new DatagramPacket(buffer, buffer.length);
                sock.receive(reply);
                byte[] data = reply.getData();
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
                res.putInt(0);
                res.putInt(0);
                res.putInt(0);
                res.putInt(0);
                resp = new DatagramPacket(res.array(),res.limit(),reply.getAddress(),reply.getPort() );
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
        Graficos.Server server = new Graficos.Server(7200);
        server.start();
        while(true) {
            idRequest = 0;
            previous = 300;
            setPlane(g);
            if (draw==true){
                g.setColor(Color.ORANGE);
            }else{
                g.setColor(Color.BLACK);
            }
            for( int i=0; i < 800; i++ ){
                server.receive();
                if ( idRequest < server.getID() )
                    i--;
                else{
                    idRequest++;
                    g.drawLine( i,previous,server.getX(), server.getY() );
                    System.out.println("X: " + server.getX() + " Y: " +server.getY());
                    previous = server.getY();
                }
                server.response(idRequest);
            }
            draw=!draw;
        }
    }
    
    private static void setPlane( Graphics g){
        g.setColor(Color.WHITE);
        g.drawLine(400,0,400,700);
        g.drawLine(0,300,900,300);
        g.setColor(Color.BLUE);
        g.drawLine(0,300,0,420);
        g.drawLine(0,420,320,167);
        g.drawLine(320,167,320,420);
        g.drawLine(320,420,640,167);
        g.drawLine(640,167,640,420);
        g.drawLine(640,420,800,300);
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
        super.setBackground(Color.BLACK);
        super.setTitle("Servidor Gráfico");
        super.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        pack();
    }                    

    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(() -> {
            new Graficos().setVisible(true);
        });
    }
}
