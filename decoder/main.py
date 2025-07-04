import speech_recognition as sr
import sounddevice
import serial


def recognize_speech_from_mic(recognizer, microphone):
	"""Transcribe speech from recorded from `microphone`.

	Returns a dictionary with three keys:
	"success": a boolean indicating whether or not the API request was
			   successful
	"error":   `None` if no error occured, otherwise a string containing
			   an error message if the API could not be reached or
			   speech was unrecognizable
	"transcription": `None` if speech could not be transcribed,
			   otherwise a string containing the transcribed text
	"""#how
	# check that recognizer and microphone arguments are appropriate type
	if not isinstance(recognizer, sr.Recognizer):
		raise TypeError("`recognizer` must be `Recognizer` instance")

	if not isinstance(microphone, sr.Microphone):
		raise TypeError("`microphone` must be `Microphone` instance")

	# adjust the recognizer sensitivity to ambient noise and record audio
	# from the microphone
	with microphone as source:
		recognizer.adjust_for_ambient_noise(source)
		audio = recognizer.listen(source)

	# set up the response object
	response = {"success": True, "error": None, "transcription": None}

	# try recognizing the speech in the recording
	# if a RequestError or UnknownValueError exception is caught,
	#	 update the response object accordingly
	try:
		response["transcription"] = recognizer.recognize_google(audio)
	except sr.RequestError:
		# API was unreachable or unresponsive
		response["success"] = False
		response["error"] = "API unavailable"
	except sr.UnknownValueError:
		# speech was unintelligible
		response["error"] = "Unable to recognize speech"

	return response


if __name__ == "__main__":
	recognizer = sr.Recognizer()
	microphone = sr.Microphone()

	arduino = serial.Serial("/dev/ttyACM0", 9600)

	while True:
		speech = recognize_speech_from_mic(recognizer, microphone)
		print(speech)
		if speech["transcription"] != None:
			if "up" in speech["transcription"]:
				arduino.write(bytes("UP", "utf-8"))
			if "down" in speech["transcription"]:
				arduino.write(bytes("DOWN", "utf-8"))
			if "left" in speech["transcription"]:
				arduino.write(bytes("LEFT", "utf-8"))
			if "right" in speech["transcription"]:
				arduino.write(bytes("RIGHT", "utf-8"))
			if "barrel" in speech["transcription"]:
				arduino.write(bytes("BARREL", "utf-8"))
