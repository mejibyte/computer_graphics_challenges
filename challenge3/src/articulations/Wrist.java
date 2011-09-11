package articulations;

public class Wrist extends Articulation {
	double angleX;

	public Wrist() {
		super();
		angleX = 0.0;
	}

	public void setAngleX(double newAngleX){
		angleX = newAngleX;
		updateTransform();
	}

	public void increaseAngleX(double by) {
		double newAngle = angleX + by;
		newAngle = Math.min(newAngle, 90 * Math.PI / 180);
		newAngle = Math.max(newAngle, -90 * Math.PI / 180);
		setAngleX(newAngle);		
	}

	private void updateTransform() {
		t3D.rotX(angleX);
		tg.setTransform(t3D);
	}

}

