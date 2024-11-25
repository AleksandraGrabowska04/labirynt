package tile;

import java.awt.Graphics2D;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

import javax.imageio.ImageIO;

import main.LabyrinthPanel;

public class TileManager {
    
    LabyrinthPanel labPanel;
    Tile[] tile;

    int[][] gridArr;
    int gridMaxX;
    int gridMaxY;

    public TileManager(LabyrinthPanel labPanel){
        this.labPanel = labPanel;
        this.gridMaxX=0;
        this.gridMaxY=0;

        this.tile = new Tile[2];
        this.gridArr = new int[labPanel.gridLimitX][labPanel.gridLimitY];

        getTileImage();
        loadLabyrinth();
    }

    public void getTileImage() {
        try {
            tile[0] = new Tile();
            tile[0].image = ImageIO.read(getClass().getResourceAsStream("/tiles/black.png"));
            tile[1] = new Tile();
            tile[1].image = ImageIO.read(getClass().getResourceAsStream("/tiles/white.png"));

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void loadLabyrinth(){
        try {
            InputStream gridStream = getClass().getResourceAsStream("/grid.txt");
            BufferedReader gridReader = new BufferedReader(new InputStreamReader(gridStream));
            int rowCounter = 0;
            String xLine;
            while ((xLine = gridReader.readLine()) != null && rowCounter < labPanel.gridLimitY) {
                int colCounter = 0;
                String[] xSquares = xLine.split(" ");
                for(int i = 0; i < xSquares.length && i < labPanel.gridLimitX; i++) {
                    this.gridArr[i][rowCounter] = Integer.parseInt(xSquares[i]);
                    colCounter++;
                };
                if(colCounter > this.gridMaxX){
                    gridMaxX=colCounter;
                }
                rowCounter++;
            }
            gridMaxY=rowCounter;
            gridReader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void draw(Graphics2D g2){
        for (int y = 0; y < gridMaxY; y++) {
            for (int x = 0; x < gridMaxX; x++) {
                g2.drawImage(tile[gridArr[x][y]].image, (-labPanel.viewX + x - gridMaxX/2) * labPanel.tileSize + labPanel.screenWidth/2,
                                                        (-labPanel.viewY + y - gridMaxY/2) * labPanel.tileSize + labPanel.screenHeight/2,
                                                        labPanel.tileSize, labPanel.tileSize, null);
            };
        };
    }
}