package articulations;

import javax.media.j3d.Transform3D;

public class Shoulder extends Articulation {
	double angleY, angleZ;
	
	public Shoulder() {
		super();
		angleY = angleZ = 0.0;
	}
	
	public void setAngleY(double newAngleY){
		angleY = newAngleY;		
		updateTransform();
	}
	
	public void setAngleZ(double newAngleZ){
		angleZ = newAngleZ;
		updateTransform();
	}
	
	public void increaseAngleY(double by) {
		double newAngle = angleY + by;
		newAngle = Math.min(newAngle, 0 * Math.PI/180);
		newAngle = Math.max(newAngle, -180*Math.PI/180.0);
		setAngleY(newAngle);
	}
	
	public void increaseAngleZ(double by) {
		double newAngle = angleZ + by;
		newAngle = Math.min(newAngle, 90*Math.PI/180.0);
		newAngle = Math.max(newAngle, -90*Math.PI/180.0);
		setAngleZ(newAngle);		
	}
	
	private void updateTransform() {
		Transform3D y = new Transform3D();
		y.rotY(angleY);
		Transform3D z = new Transform3D();
		z.rotZ(angleZ);
		t3D.mul(y, z);
		tg.setTransform(t3D);
	}
}
