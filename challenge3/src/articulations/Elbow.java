package articulations;

import javax.media.j3d.Transform3D;

public class Elbow extends Articulation {
	double angleZ;
	
	public Elbow() {
		super();
		angleZ = 0.0;
	}
	
	public void setAngleZ(double newAngleZ){
		angleZ = newAngleZ;
		updateTransform();
	}
		
	public void increaseAngleZ(double by) {
		double newAngle = angleZ + by;
		newAngle = Math.max(newAngle, 0);
		newAngle = Math.min(newAngle, 135 * Math.PI / 180);
		setAngleZ(newAngle);		
	}
	
	private void updateTransform() {
		t3D.rotZ(angleZ);
		tg.setTransform(t3D);
	}

}
