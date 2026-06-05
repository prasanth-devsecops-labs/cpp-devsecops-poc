pipeline {
    agent any

    environment {
        S3_BUCKET = "YOUR_BUCKET_NAME_HERE"
    }

    stages {
        stage('Code Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Static Code Analysis (SAST)') {
            steps {
                echo 'Running structural code analysis via Cppcheck...'
                // Saves the report to a file. We use '|| true' so Jenkins doesn't crash if cppcheck finds errors.
                sh 'cppcheck --enable=all --output-file=cppcheck-report.txt . || true'
            }
        }

        stage('Security Flaw Analysis') {
            steps {
                echo 'Running vulnerability sweeps via Flawfinder...'
                sh 'flawfinder . > flawfinder-report.txt || true'
            }
        }

        stage('Consolidated Scan Report') {
            steps {
                echo 'Generating Security and Quality Summary Table...'
                sh '''
                echo "========================================================"
                echo "             DEVSECOPS PIPELINE SCAN SUMMARY            "
                echo "========================================================"
                printf "| %-25s | %-20s |\\n" "SCAN TYPE" "METRIC / COUNT"
                echo "--------------------------------------------------------"
                
                # Extract Cppcheck counts
                CPP_ERRORS=$(grep -c ": error:" cppcheck-report.txt || echo "0")
                CPP_WARNS=$(grep -c ": warning:" cppcheck-report.txt || echo "0")
                printf "| %-25s | %-20s |\\n" "Cppcheck Total Errors" "$CPP_ERRORS"
                printf "| %-25s | %-20s |\\n" "Cppcheck Total Warnings" "$CPP_WARNS"
                
                # Extract Flawfinder counts
                FLAW_HITS=$(grep -i "Hits =" flawfinder-report.txt | awk '{print $3}' || echo "0")
                printf "| %-25s | %-20s |\\n" "Flawfinder Vulnerabilities" "$FLAW_HITS"
                
                echo "========================================================"
                '''
            }
        }

        stage('Compile Binary') {
            steps {
                echo 'Compiling C++ Source Code...'
                sh 'make clean && make'
            }
        }

        stage('Runtime Security & Leak Analysis') {
            steps {
                echo 'Executing application under Valgrind binary monitor...'
                sh 'valgrind --leak-check=full --error-exitcode=1 ./my_secure_app'
            }
        }

        stage('Archive Artifact to Cloud') {
            steps {
                echo 'Pushing verified executable file to Amazon S3 securely...'
                sh 'aws s3 cp my_secure_app s3://${S3_BUCKET}/builds/my_secure_app-${BUILD_NUMBER}'
            }
        }
    }

    post {
        always {
            echo 'Cleaning up workspaces...'
            cleanWs()
        }
    }
}




// -------------
// pipeline {
//     agent any

//     environment {
//         S3_BUCKET = "devops-cpp-artifacts-2026-prasanth"
//     }

//     stages {
//         stage('Code Checkout') {
//             steps {
//                 checkout scm
//             }
//         }

//         stage('Static Code Analysis (SAST)') {
//             steps {
//                 echo 'Running structural code analysis via Cppcheck...'
//                 // Scans for logical bugs, layout problems, and memory slip-ups
//                 sh 'cppcheck --enable=all --output-file=cppcheck-report.txt .'
//                 sh 'cat cppcheck-report.txt'
//             }
//         }

//         stage('Security Flaw Analysis') {
//             steps {
//                 echo 'Running vulnerability sweeps via Flawfinder...'
//                 // Identifies risky functions like strcpy that cause system-level exploits
//                 sh 'flawfinder . > flawfinder-report.txt'
//                 sh 'cat flawfinder-report.txt'
//             }
//         }

//         stage('Compile Binary') {
//             steps {
//                 echo 'Compiling C++ Source Code using Makefile rules...'
//                 sh 'make clean && make'
//             }
//         }

//         stage('Runtime Security & Leak Analysis') {
//             steps {
//                 echo 'Executing application under Valgrind binary monitor...'
//                 // Tracks exact memory usage. If memory leaks occur, Valgrind forces an exit code of 1, failing the build stage.
//                 sh 'valgrind --leak-check=full --error-exitcode=1 ./my_secure_app'
//             }
//         }

//         stage('Archive Artifact to Cloud') {
//             steps {
//                 echo 'Pushing verified executable file to Amazon S3 securely...'
//                 sh 'aws s3 cp my_secure_app s3://${S3_BUCKET}/builds/my_secure_app-${BUILD_NUMBER}'
//             }
//         }
//     }

//     post {
//         always {
//             echo 'Cleaning up workspaces...'
//             cleanWs()
//         }
//     }
// }
