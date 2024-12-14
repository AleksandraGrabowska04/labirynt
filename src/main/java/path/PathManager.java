package path;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import static java.lang.System.currentTimeMillis;

import javax.imageio.ImageIO;

import main.KeyHandler;
import main.LabyrinthPanel;
import tile.Tile;
import tile.TileManager;

public class PathManager {
    LabyrinthPanel labPanel;
    TileManager tileMng;
    Tile[] tile;

    int pathState;
    long pathStateTime;

    int[][] pathArr;
    int pathMax;

    int frameCounter;
    int pathCounter;

    public PathManager(LabyrinthPanel labPanel, TileManager tileMng){
        this.labPanel = labPanel;
        this.tileMng = tileMng;
        this.tile = new Tile[1022];

        this.pathState = 0;
        this.pathStateTime = currentTimeMillis();

        this.pathArr = new int[labPanel.pathLimit][2];
        this.pathMax = 0;

        this.frameCounter = 0;
        this.pathCounter = 0;

        getTileImage();
        loadPath();
    }

    public void getTileImage() {
        try {
            tile[0] = new Tile();
            tile[0].image = ImageIO.read(getClass().getResourceAsStream("/tiles/white.png"));
            for (int i = 1; i <= 1021; i++) {
                tile[i] = new Tile();
                tile[i].image = new BufferedImage(tile[0].image.getWidth(), tile[0].image.getHeight(), BufferedImage.TYPE_INT_ARGB);
                int rgb = new Color(Math.max(Math.min(i-510, 255),0), Math.min(Math.min(i, 255),  Math.max(1020-i, 0)), Math.max(Math.min(510-i,255), 0),255).getRGB();
                for (int x = 0; x < tile[0].image.getWidth(); x++) {
                    for (int y = 0; y < tile[0].image.getHeight(); y++) {
                        tile[i].image.setRGB(x, y, tile[0].image.getRGB(x,y) & rgb);
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void loadPath(){
        try {
            InputStream pathStream = getClass().getResourceAsStream("/path.txt");
            BufferedReader pathReader = new BufferedReader(new InputStreamReader(pathStream));
            String pathLine;
            for (int i = 0; (i < labPanel.pathLimit) && (pathLine = pathReader.readLine()) != null; i++) {
                String[] pathDataIn = pathLine.split(" ");
                pathArr[i][1] = Integer.parseInt(pathDataIn[0]);
                pathArr[i][0] = Integer.parseInt(pathDataIn[1]);
                this.pathMax++;
            }
            pathReader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void update(KeyHandler keyH){
        if((currentTimeMillis() - this.pathStateTime > 2000) && (keyH.inputSpace == true)){
            switch(this.pathState) {
                case 0 -> {
                    this.pathState = 1;
                }
                case 1 -> {
                    this.pathState = 2;
                    this.pathCounter = this.pathMax;
                }
                case 2 -> {
                    this.pathState = 0;
                    this.pathCounter = 0;
                }
            }
            this.pathStateTime = currentTimeMillis();
        }
        if(this.pathState == 1){
            if(this.pathCounter < this.pathMax){
                this.frameCounter++;
                if (this.frameCounter>5){
                    this.frameCounter = 0;
                    this.pathCounter++;
                }
            }
        }
    }

    public void draw(Graphics2D g2){
        for (int i = 0; pathCounter > 0 && i < pathCounter && this.pathState != 0; i++) {
            g2.drawImage(tile[i*1020/(Math.max(pathCounter-1, 1))+1].image, (-labPanel.viewX + pathArr[i][0] - tileMng.gridMaxX/2) * labPanel.tileSize + labPanel.screenWidth/2,
                                        (-labPanel.viewY + pathArr[i][1] - tileMng.gridMaxY/2) * labPanel.tileSize + labPanel.screenHeight/2,
                                        labPanel.tileSize, labPanel.tileSize, null);

        };
    }
}
