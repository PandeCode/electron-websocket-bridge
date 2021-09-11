$ = document.querySelector.bind(document);

const servers = {
	iceServers: [
		{
			urls: [
				"stun:stun1.l.google.com:19302",
				"stun:stun2.l.google.com:19302",
			],
		},
	],
	iceCandidatePoolSize: 10,
};

function activateWebRTC() {
	const peerConnection = new RTCPeerConnection(servers);
	let localStream = null;
	let remoteStream = null;
}

document.addEventListener("load", () => {
	$("#activateWebRTCBtn").addEventListener("click", () => activateWebRTC());
});
