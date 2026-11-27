export module collision;

import rectangle;

export namespace shootemup {
    bool intersects(Rectangle  first, Rectangle  second) {

        //cas 1
        if (first.x + first.width <= second.x) {
            return false;
        }

        // caas 2
        if (first.x >= second.x + second.width) {
            return false;
        }

        //cas 3
        if (first.y + first.height <= second.y) {
            return false;
        }

        // cas 4
        if (first.y >= second.y + second.height) {
            return false;
        }
        return true;
    }
}




