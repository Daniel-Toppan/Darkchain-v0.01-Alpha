import static org.gradle.api.JavaVersion.VERSION_1_8

/*
 * Gradle script plugin: Configure a module such that Java and Kotlin
 * are always compiled for Java 8.
 */
apply plugin: 'kotlin'

tasks.withType(AbstractCompile).configureEach {
    // This is a bit ugly, but Gradle isn't recognising the KotlinCompile task
    // as it does the built-in JavaCompile task.
    if (it.class.name.startsWith('org.jetbrains.kotlin.gradle.tasks.KotlinCompile')) {
        kotlinOptions {
            jvmTarget = VERSION_1_8
        }
    }
}

tasks.withType(JavaCompile).configureEach {
    sourceCompatibility = VERSION_1_8
    targetCompatibility = VERSION_1_8

     
      import static org.gradle.api.JavaVersion.VERSION_1_8

/*
 * Gradle script plugin: Configure a module such that the Java and Kotlin
 * compilers use the deterministic rt.jar instead of the full JDK rt.jar.
 */
apply plugin: 'kotlin'

evaluationDependsOn(':jdk8u-deterministic')

def jdk8uDeterministic = project(':jdk8u-deterministic')

ext {
    jdkTask = jdk8uDeterministic.tasks.named('assemble')
    deterministic_jdk_home = jdk8uDeterministic.jdk_home
    deterministic_rt_jar = jdk8uDeterministic.rt_jar
}

tasks.withType(AbstractCompile).configureEach {
    dependsOn jdkTask

    // This is a bit ugly, but Gradle isn't recognising the KotlinCompile task
    // as it does the built-in JavaCompile task.
    if (it.class.name.startsWith('org.jetbrains.kotlin.gradle.tasks.KotlinCompile')) {
        kotlinOptions {
            jdkHome = deterministic_jdk_home
            jvmTarget = VERSION_1_8
        }
    }
}

tasks.withType(JavaCompile).configureEach {
    options.compilerArgs << '-bootclasspath' << deterministic_rt_jar
    sourceCompatibility = VERSION_1_8
    targetCompatibility = VERSION_1_8
}
  
  ###  source.c darkchain exe.
  
  import com.r3.testing.DistributeTestsBy
import com.r3.testing.PodLogLevel

import static org.gradle.api.JavaVersion.VERSION_11
import static org.gradle.api.JavaVersion.VERSION_1_8

buildscript {
    // For sharing constants between builds
    Properties constants = new Properties()
    file("$projectDir/constants.properties").withInputStream { constants.load(it) }

    // Our version: bump this on release.
    ext.baseVersion = constants.getProperty("cordaVersion")
    ext.versionSuffix = constants.getProperty("versionSuffix")

    ext.corda_platform_version = constants.getProperty("platformVersion")
    ext.gradle_plugins_version = constants.getProperty("gradlePluginsVersion")

    // Dependency versions. Can run 'gradle dependencyUpdates' to find new versions of things.
    //
    // TODO: Sort this alphabetically.
    ext.kotlin_version = constants.getProperty("kotlinVersion")
    ext.warnings_as_errors = project.hasProperty("compilation.warningsAsErrors") ? project.property("compilation.warningsAsErrors").toBoolean() : false

    ext.quasar_group = 'co.paralleluniverse'
    // Set version of Quasar according to version of Java used:
    if (JavaVersion.current().isJava8()) {
        ext.quasar_version = constants.getProperty("quasarVersion")
        ext.quasar_classifier = constants.getProperty("quasarClassifier")
        ext.jdkClassifier = constants.getProperty("jdkClassifier")
    } else {
        ext.quasar_version = constants.getProperty("quasarVersion11")
        ext.quasar_classifier = constants.getProperty("quasarClassifier11")
        ext.jdkClassifier = constants.getProperty("jdkClassifier11")
    }
    ext.cordaScanApiClassifier = jdkClassifier
    ext.quasar_exclusions = [
            'co.paralleluniverse**',
            'groovy**',
            'com.esotericsoftware.**',
            'jdk**',
            'junit**',
            'kotlin**',
            'net.rubygrapefruit.**',
            'org.gradle.**',
            'org.apache.**',
            'org.jacoco.**',
            'org.junit**',
            'org.slf4j**',
            'worker.org.gradle.**',
            'com.nhaarman.mockito_kotlin**',
            'org.assertj**',
            'org.hamcrest**',
            'org.mockito**',
            'org.opentest4j**'
    ]

    // gradle-capsule-plugin:1.0.2 contains capsule:1.0.1 by default.
    // We must configure it manually to use the latest capsule version.
    ext.capsule_version = '1.0.3'

    ext.asm_version = '7.1'
    ext.artemis_version = '2.6.2'
    // TODO Upgrade Jackson only when corda is using kotlin 1.3.10
    ext.jackson_version = '2.9.7'
    ext.jetty_version = '9.4.19.v20190610'
    ext.jersey_version = '2.25'
    ext.servlet_version = '4.0.1'
    ext.assertj_version = '3.12.2'
    ext.slf4j_version = '1.7.30'
    ext.log4j_version = '2.13.3'
    ext.bouncycastle_version = constants.getProperty("bouncycastleVersion")
    ext.guava_version = constants.getProperty("guavaVersion")
    ext.caffeine_version = constants.getProperty("caffeineVersion")
    ext.disruptor_version = constants.getProperty("disruptorVersion")
    ext.metrics_version = constants.getProperty("metricsVersion")
    ext.metrics_new_relic_version = constants.getProperty("metricsNewRelicVersion")
    ext.djvm_version = constants.getProperty("djvmVersion")
    ext.deterministic_rt_version = constants.getProperty('deterministicRtVersion')
    ext.okhttp_version = '3.14.2'
    ext.netty_version = '4.1.46.Final'
    ext.tcnative_version = '2.0.29.Final'
    ext.typesafe_config_version = constants.getProperty("typesafeConfigVersion")
    ext.fileupload_version = '1.4'
    ext.kryo_version = '4.0.2'
    ext.kryo_serializer_version = '0.43'
    // Legacy JUnit 4 version
    ext.junit_version = '4.12'
    // Need this version to access classpath scanning error handling fix -
    // see https://github.com/junit-team/junit5/commit/389de48c2a18c5a93a7203ef424aa47a8a835a74
    // Upgrade to 5.5.x when GA release is available.
    ext.junit_vintage_version = '5.5.0-RC1'
    ext.junit_jupiter_version = '5.5.0-RC1'
    ext.junit_platform_version = '1.5.0-RC1'
    ext.mockito_version = '2.28.2'
    ext.mockito_kotlin_version = '1.6.0'
    ext.hamkrest_version = '1.7.0.0'
    ext.jopt_simple_version = '5.0.2'
    ext.jansi_version = '1.18'
    ext.hibernate_version = '5.4.3.Final'
    ext.h2_version = '1.4.199' // Update docs if renamed or removed.
    ext.rxjava_version = '1.3.8'
    ext.dokka_version = '0.9.17'
    ext.eddsa_version = '0.3.0'
    ext.dependency_checker_version = '5.2.0'
    ext.commons_collections_version = '4.3'
    ext.beanutils_version = '1.9.4'
    ext.crash_version = '1.7.4'
    ext.jsr305_version = constants.getProperty("jsr305Version")
    ext.shiro_version = '1.4.1'
    ext.artifactory_plugin_version = constants.getProperty('artifactoryPluginVersion')
    ext.hikari_version = '3.3.1'
    ext.liquibase_version = '3.6.3'
    ext.artifactory_contextUrl = 'https://software.r3.com/artifactory'
    ext.snake_yaml_version = constants.getProperty('snakeYamlVersion')
    ext.docker_compose_rule_version = '0.35.0'
    ext.selenium_version = '3.141.59'
    ext.ghostdriver_version = '2.1.0'
    ext.proguard_version = constants.getProperty('proguardVersion')
    ext.jsch_version = '0.1.55'
    ext.protonj_version = '0.33.0' // Overide Artemis version
    ext.snappy_version = '0.4'
    ext.class_graph_version = constants.getProperty('classgraphVersion')
    ext.jcabi_manifests_version = '1.1'
    ext.picocli_version = '3.9.6'
    ext.commons_lang_version = '3.9'
    ext.commons_io_version = '2.6'
    ext.controlsfx_version = '8.40.15'
    ext.detekt_version = constants.getProperty('detektVersion')
    ext.docker_java_version = constants.getProperty("dockerJavaVersion")
    if (JavaVersion.current().isJava8()) {
        ext.fontawesomefx_commons_version = '8.15'
        ext.fontawesomefx_fontawesome_version = '4.7.0-5'
    } else {
        // has been compiled by a more recent version of the Java Runtime (class file version 55.0)
        ext.fontawesomefx_commons_version = '11.0'
        ext.fontawesomefx_fontawesome_version = '4.7.0-11'
    }

    // Name of the IntelliJ SDK created for the deterministic Java rt.jar.
    // ext.deterministic_idea_sdk = '1.8 (Deterministic)'

    // Update 121 is required for ObjectInputFilter.
    // Updates [131, 161] also have zip compression bugs on MacOS (High Sierra).
    // when the java version in NodeStartup.hasMinimumJavaVersion() changes, so must this check
    ext.java8_minUpdateVersion = constants.getProperty('java8MinUpdateVersion')
    ext.corda_revision = {
        try {
            "git rev-parse HEAD".execute().text.trim()
        } catch (Exception ignored) {
            logger.warn("git is unavailable in build environment")
            "unknown"
        }
    }()
    ext.corda_docs_link = "https://docs.corda.net/docs/corda-os/$baseVersion"
    repositories {
        mavenLocal()
        // Use system environment to activate caching with Artifactory,
        // because it is actually easier to pass that during parallel build.
        // NOTE: it has to be a name of a virtual repository with all
        // required remote or local repositories!
        if (System.getenv("CORDA_USE_CACHE")) {
            maven {
                name "R3 Maven remote repositories"
                url "${artifactory_contextUrl}/${System.getenv("CORDA_USE_CACHE")}"
                authentication {
                    basic(BasicAuthentication)
                }
                credentials {
                    username = System.getenv('CORDA_ARTIFACTORY_USERNAME')
                    password = System.getenv('CORDA_ARTIFACTORY_PASSWORD')
                }
            }
        } else {
            maven {
                url "${artifactory_contextUrl}/corda-dependencies-dev"
                content {
                    includeGroupByRegex 'net\\.corda(\\..*)?'
                    includeGroupByRegex 'com\\.r3(\\..*)?'
                }
            }
            maven {
                url "${artifactory_contextUrl}/corda-releases"
                content {
                    includeGroupByRegex 'net\\.corda(\\..*)?'
                    includeGroupByRegex 'com\\.r3(\\..*)?'
                }
            }
            mavenCentral()
            jcenter()
            maven {
                url 'https://kotlin.bintray.com/kotlinx'
                content {
                    includeGroup 'org.jetbrains.kotlin'
                }
            }
        }
    }
    dependencies {
        classpath "org.jetbrains.kotlin:kotlin-gradle-plugin:$kotlin_version"
        classpath "org.jetbrains.kotlin:kotlin-allopen:$kotlin_version"
        classpath "net.corda.plugins:publish-utils:$gradle_plugins_version"
        classpath "net.corda.plugins:quasar-utils:$gradle_plugins_version"
        classpath "net.corda.plugins:cordformation:$gradle_plugins_version"
        classpath "net.corda.plugins:cordapp:$gradle_plugins_version"
        classpath "net.corda.plugins:api-scanner:$gradle_plugins_version"
        classpath "net.corda.plugins:jar-filter:$gradle_plugins_version"
        classpath "net.sf.proguard:proguard-gradle:$proguard_version"
        classpath 'com.github.ben-manes:gradle-versions-plugin:0.15.0'
        classpath "org.jetbrains.kotlin:kotlin-noarg:$kotlin_version"
        classpath "org.jetbrains.dokka:dokka-gradle-plugin:${dokka_version}"
        classpath "net.i2p.crypto:eddsa:$eddsa_version" // Needed for ServiceIdentityGenerator in the build environment.
        classpath "org.owasp:dependency-check-gradle:${dependency_checker_version}"
        classpath "org.jfrog.buildinfo:build-info-extractor-gradle:$artifactory_plugin_version"
        // Capsule gradle plugin forked and maintained locally to support Gradle 5.x
        // See https://github.com/corda/gradle-capsule-plugin
        classpath "us.kirchmeier:gradle-capsule-plugin:1.0.4_r3"
        classpath group: "com.r3.testing", name: "gradle-distributed-testing-plugin", version: '1.3.0'
        classpath "org.sonarsource.scanner.gradle:sonarqube-gradle-plugin:2.8"
    }

    configurations.all {
        resolutionStrategy.cacheChangingModulesFor 0, 'seconds'
    }
}

plugins {
    // Add the shadow plugin to the plugins classpath for the entire project.
    id 'com.github.johnrengelman.shadow' version '2.0.4' apply false
    id "com.gradle.build-scan" version "2.2.1"
    id "org.ajoberstar.grgit" version "4.0.0"
}

apply plugin: 'project-report'
apply plugin: 'com.github.ben-manes.versions'
apply plugin: 'net.corda.plugins.publish-utils'
apply plugin: 'com.jfrog.artifactory'
apply plugin: 'com.r3.testing.distributed-testing'


// If the command line project option -PversionFromGit is added to the gradle invocation, we'll resolve 
// the latest git commit hash and timestamp and create a version postfix from that
if (project.hasProperty("versionFromGit")){
    ext.versionSuffix = "${grgit.head().dateTime.format("yyyyMMdd_HHmmss")}-${grgit.head().abbreviatedId}"
}

// Need the `toString()` call on these, because they need to be converted from GStringImpl to Java Strings.
if (ext.versionSuffix != ""){
    ext.corda_release_version = "${ext.baseVersion}-${ext.versionSuffix}".toString()
} else {
    ext.corda_release_version = "${ext.baseVersion}".toString()
}

// We need the following three lines even though they're inside an allprojects {} block below because otherwise
// IntelliJ gets confused when importing the project and ends up erasing and recreating the .idea directory, along
// with the run configurations. It also doesn't realise that the project is a Java 8 project and misconfigures
// the resulting import. This fixes it.
apply plugin: 'java'

logger.lifecycle("Java version: {}", JavaVersion.current())
sourceCompatibility = VERSION_1_8
targetCompatibility = JavaVersion.current().isJava8() ? VERSION_1_8 : VERSION_11
logger.lifecycle("Java source compatibility: {}", sourceCompatibility)
logger.lifecycle("Java target compatibility: {}", targetCompatibility)
logger.lifecycle("Quasar version: {}", quasar_version)
logger.lifecycle("Quasar classifier: {}", quasar_classifier.toString())
logger.lifecycle("Building Corda version: {}", corda_release_version)

allprojects {
    apply plugin: 'kotlin'
    apply plugin: 'jacoco'
    apply plugin: 'org.owasp.dependencycheck'
    apply plugin: 'kotlin-allopen'
    apply plugin: 'org.sonarqube'

    allOpen {
        annotations(
                "javax.persistence.Entity",
                "javax.persistence.Embeddable",
                "javax.persistence.MappedSuperclass"
        )
    }

    dependencyCheck {
        suppressionFile = '.ci/dependency-checker/suppressedLibraries.xml'
        cveValidForHours = 1
        format = 'ALL'
        failOnError = project.property('owasp.failOnError')
        // by default CVSS is '11' which passes everything. Set between 0-10 to catch vulnerable deps
        failBuildOnCVSS = project.property('owasp.failBuildOnCVSS').toFloat()

        analyzers {
            assemblyEnabled = false
            nuspecEnabled = false
            nugetconfEnabled = false
        }
    }
    sourceCompatibility = VERSION_1_8
    targetCompatibility = JavaVersion.current().isJava8() ? VERSION_1_8 : VERSION_11

    jacoco {
        // JDK11 official support (https://github.com/jacoco/jacoco/releases/tag/v0.8.3)
        toolVersion = "0.8.3"
    }

    tasks.withType(JavaCompile).configureEach {
        options.compilerArgs << "-Xlint:unchecked" << "-Xlint:deprecation" << "-Xlint:-options" << "-parameters"
        options.compilerArgs << '-XDenableSunApiLintControl'
        if (warnings_as_errors) {
            // We cannot fail the build on compiler warnings because we have java warnings that you cannot disable:
            // Signal is internal proprietary API and may be removed in a future release
            // otherwise we should have the following line here:
            // options.compilerArgs << "-Werror"
        }
        options.encoding = 'UTF-8'
    }

    tasks.withType(org.jetbrains.kotlin.gradle.tasks.KotlinCompile).configureEach {
        kotlinOptions {
            languageVersion = "1.2"
            apiVersion = "1.2"
            jvmTarget = VERSION_1_8
            javaParameters = true   // Useful for reflection.
            freeCompilerArgs = ['-Xjvm-default=compatibility']
            allWarningsAsErrors = warnings_as_errors
        }
    }

    tasks.register('compileAll') { task ->
        task.dependsOn tasks.withType(AbstractCompile)
    }

    tasks.withType(Jar).configureEach { task ->
        // Includes War and Ear
        manifest {
            attributes('Corda-Release-Version': corda_release_version)
            attributes('Corda-Platform-Version': corda_platform_version)
            attributes('Corda-Revision': corda_revision)
            attributes('Corda-Vendor': 'Corda Open Source')
            attributes('Automatic-Module-Name': "net.corda.${task.project.name.replaceAll('-', '.')}")
            attributes('Corda-Docs-Link': corda_docs_link)
        }
    }
    
    tasks.withType(Test).configureEach {
        forkEvery = 20
        ignoreFailures = project.hasProperty('tests.ignoreFailures') ? project.property('tests.ignoreFailures').toBoolean() : false
        failFast = project.hasProperty('tests.failFast') ? project.property('tests.failFast').toBoolean() : false

        // Prevent the project from creating temporary files outside of the build directory.
        systemProperty 'java.io.tmpdir', buildDir.absolutePath

        maxHeapSize = "1g"

        if (project.path.startsWith(':experimental') && System.getProperty("experimental.test.enable") == null) {
            enabled = false
        }

        // Required to use Gradle build cache (until Gradle 5.0 is released with default value of "append" set to false)
        // See https://github.com/gradle/gradle/issues/5269 and https://github.com/gradle/gradle/pull/6419
        extensions.configure(TypeOf.typeOf(JacocoTaskExtension)) { ex ->
            ex.append = false
        }

        maxParallelForks = (System.env.CORDA_TESTING_FORKS == null) ? 1 : "$System.env.CORDA_TESTING_FORKS".toInteger()

        systemProperty 'java.security.egd', 'file:/dev/./urandom'
    }

    tasks.withType(Test).configureEach {
        if (name.contains("integrationTest")) {
            maxParallelForks = (System.env.CORDA_INT_TESTING_FORKS == null) ? 1 : "$System.env.CORDA_INT_TESTING_FORKS".toInteger()
        }
    }

    if (jdkClassifier) {
        jar {
            // JDK11 built and published artifacts to include classifier
            archiveClassifier = jdkClassifier
        }
    }

    group 'net.corda'
    version "$corda_release_version"

    repositories {
        mavenLocal()
        // Use system environment to activate caching with Artifactory,
        // because it is actually easier to pass that during parallel build.
        // NOTE: it has to be a name of a virtual repository with all
        // required remote or local repositories!
        if (System.getenv("CORDA_USE_CACHE")) {
            maven {
                name "R3 Maven remote repositories"
                url "${artifactory_contextUrl}/${System.getenv("CORDA_USE_CACHE")}"
                authentication {
                    basic(BasicAuthentication)
                }
                credentials {
                    username = System.getenv('CORDA_ARTIFACTORY_USERNAME')
                    password = System.getenv('CORDA_ARTIFACTORY_PASSWORD')
                }
            }
        } else {
            maven {
                url "${artifactory_contextUrl}/corda-dependencies"
                content {
                    includeGroupByRegex 'net\\.corda(\\..*)?'
                    includeGroupByRegex 'com\\.r3(\\..*)?'
                    includeGroup 'co.paralleluniverse'
                    includeGroup 'org.crashub'
                    includeGroup 'com.github.bft-smart'
                }
            }
            maven {
                url "${artifactory_contextUrl}/corda-dev"
                content {
                    includeGroupByRegex 'net\\.corda(\\..*)?'
                    includeGroupByRegex 'com\\.r3(\\..*)?'
                }
            }
            maven {
                url 'https://repo.gradle.org/gradle/libs-releases'
                content {
                    includeGroup 'org.gradle'
                    includeGroup 'com.github.detro'
                }
            }
            mavenCentral()
            jcenter()
        }
    }

    configurations {
        all {
            resolutionStrategy {
                // Force dependencies to use the same version of Kotlin as Corda.
                force "org.jetbrains.kotlin:kotlin-stdlib-jdk7:$kotlin_version"
                force "org.jetbrains.kotlin:kotlin-stdlib-jdk8:$kotlin_version"
                force "org.jetbrains.kotlin:kotlin-reflect:$kotlin_version"

                // Force dependencies to use the same version of Guava as Corda.
                force "com.google.guava:guava:$guava_version"

                // Demand that everything uses our given version of Netty.
                eachDependency { details ->
                    if (details.requested.group == 'io.netty' && details.requested.name.startsWith('netty-')) {
                        if (details.requested.name.startsWith('netty-tcnative')){
                            details.useVersion tcnative_version
                        } else {
                            details.useVersion netty_version
                        }
                    }
                }
            }
        }
        compile {
            // We want to use SLF4J's version of these bindings: jcl-over-slf4j
            // Remove any transitive dependency on Apache's version.
            exclude group: 'commons-logging', module: 'commons-logging'
            // Remove any transitive dependency on Logback (e.g. Liquibase 3.6 introduces this dependency)
            exclude group: 'ch.qos.logback'

            // Netty-All is an uber-jar which contains every Netty module.
            // Exclude it to force us to use the individual Netty modules instead.
            exclude group: 'io.netty', module: 'netty-all'
        }
        runtime {
            // We never want isolated.jar on classPath, since we want to test jar being dynamically loaded as an attachment
            exclude module: 'isolated'
        }
    }
}
sonarqube {
    properties {
        property "sonar.projectName", "Corda"
        property "sonar.projectKey", "corda"
        property 'sonar.tests', '**/src/test/**,**/src/smoke-test/**,**/src/integration-test/**,**/src/integration-test-slow/**'
        property 'sonar.coverage.jacoco.xmlReportPaths', "${rootDir.path}/build/reports/jacoco/jacocoRootReport/jacocoRootReport.xml"
        property 'detekt.sonar.kotlin.baseline.path', "${rootDir.path}/detekt-baseline.xml"
        property 'detekt.sonar.kotlin.config.path', "${rootDir.path}/detekt-config.yml"
    }
}

// Check that we are running on a Java 8 JDK. The source/targetCompatibility values above aren't sufficient to
// guarantee this because those are properties checked by the Java plugin, but we're using Kotlin.
//
// We recommend a specific minor version (unfortunately, not checkable directly) because JavaFX adds APIs in
// minor releases, so we can't work with just any Java 8, it has to be a recent one.
if (!JavaVersion.current().java8Compatible)
    throw new GradleException("Corda requires Java 8, please upgrade to at least 1.8.0_$java8_minUpdateVersion")

configurations {
    detekt
}

// Required for building out the fat JAR.
dependencies {
    compile project(':node')
    compile "com.google.guava:guava:$guava_version"

    // Set to corda compile to ensure it exists now deploy nodes no longer relies on build
    compile project(path: ":node:capsule", configuration: 'runtimeArtifacts')
    compile project(path: ":testing:testserver:testcapsule:", configuration: 'runtimeArtifacts')

    // For the buildCordappDependenciesJar task
    runtime project(':client:jfx')
    runtime project(':client:mock')
    runtime project(':client:rpc')
    runtime project(':core')
    runtime project(':confidential-identities')
    runtime project(':finance:workflows')
    runtime project(':finance:contracts')
    runtime project(':testing:testserver')
    testCompile project(':test-utils')
    detekt 'io.gitlab.arturbosch.detekt:detekt-cli:1.0.1'
}

jar {
    // Prevent the root project from building an unwanted dummy CorDapp.
    enabled = false
}

task jacocoRootReport(type: org.gradle.testing.jacoco.tasks.JacocoReport) {
    dependsOn = subprojects.test
    additionalSourceDirs = files(subprojects.sourceSets.main.allSource.srcDirs)
    sourceDirectories = files(subprojects.sourceSets.main.allSource.srcDirs)
    classDirectories = files(subprojects.sourceSets.main.output)
    executionData = files(subprojects.jacocoTestReport.executionData)
    reports {
        html.enabled = true
        xml.enabled = true
        csv.enabled = false
    }
    onlyIf = {
        true
    }
    doFirst {
        executionData = files(executionData.findAll {
            it.exists()
        })
    }
    afterEvaluate {
        classDirectories = files(classDirectories.files.collect {
            fileTree(dir: it,
                    // these exclusions are necessary because jacoco gets confused by same class names
                    // which occur due to deterministic versions of non deterministic classes
                    exclude: ['**/net/corda/core/crypto/DigestSupplier**',
                    '**/net/corda/core/crypto/DelegatingSecureRandomService',
                    '**/net/corda/core/internal/ThreadLocalToggleField**',
                    '**/net/corda/core/internal/InheritableThreadLocalToggleField**',
                    '**/net/corda/core/internal/ToggleField**',
                    'net/corda/core/internal/rules/StateContractValidationEnforcementRule**',
                    'net/corda/core/internal/SimpleToggleField**',
                    'net/corda/core/serialization/SerializationFactory**',
                    'net/corda/serialization/internal/amqp/AMQPStreams**',
                    'net/corda/serialization/internal/amqp/AMQPSerializerFactories**',
                    'net/corda/serialization/internal/amqp/AMQPSerializationThreadContext**',
                    'net/corda/serialization/internal/ByteBufferStreams**',
                    'net/corda/serialization/internal/model/DefaultCacheProvider**',
                    'net/corda/serialization/internal/DefaultWhitelist**'
                    ])
        })
    }
}

tasks.register('detekt', JavaExec) {
    def input = "$projectDir"
    def config = "$projectDir/detekt-config.yml"
    def baseline = "$projectDir/detekt-baseline.xml"
    def detektPluginsJar = project(':detekt-plugins').tasks.jar
    def plugins = detektPluginsJar.outputs.files.singleFile
    def params = ['-i', input, '-c', config, '-b', baseline, '--plugins', plugins]
    inputs.files(detektPluginsJar, config, baseline)
    main = "io.gitlab.arturbosch.detekt.cli.Main"
    classpath = configurations.detekt
    args(params)
}

tasks.register('detektBaseline', JavaExec) {
    main = "io.gitlab.arturbosch.detekt.cli.Main"
    classpath = configurations.detekt
    def input = "$projectDir"
    def config = "$projectDir/detekt-config.yml, $projectDir/detekt-baseline-config.yml"
    def baseline = "$projectDir/detekt-baseline.xml"
    def params = ['-i', input, '-c', config, '-b', baseline, '--create-baseline']
    args(params)
}

tasks.withType(Test).configureEach {
    reports.html.destination = file("${reporting.baseDir}/${name}")
}

task testReport(type: TestReport) {
    destinationDir = file("$buildDir/reports/allTests")
    // Include the results from the `test` task in all subprojects
    reportOn subprojects*.test
}

bintrayConfig {
    user = System.getenv('CORDA_BINTRAY_USER')
    key = System.getenv('CORDA_BINTRAY_KEY')
    repo = 'corda'
    org = 'r3'
    licenses = ['Apache-2.0']
    vcsUrl = 'https://github.com/corda/corda'
    projectUrl = 'https://github.com/corda/corda'
    gpgSign = true
    gpgPassphrase = System.getenv('CORDA_BINTRAY_GPG_PASSPHRASE')
    publications = [
            'corda-jfx',
            'corda-mock',
            'corda-rpc',
            'corda-core',
            'corda-core-deterministic',
            'corda-deterministic-verifier',
            'corda-deserializers-djvm',
            'corda',
            'corda-finance-workflows',
            'corda-finance-contracts',
            'corda-node',
            'corda-node-api',
            'corda-node-djvm',
            'corda-test-common',
            'corda-core-test-utils',
            'corda-test-utils',
            'corda-test-db',
            'corda-jackson',
            'corda-testserver-impl',
            'corda-testserver',
            'corda-node-driver',
            'corda-confidential-identities',
            'corda-shell',
            'corda-tools-shell-cli',
            'corda-serialization',
            'corda-serialization-deterministic',
            'corda-serialization-djvm',
            'corda-tools-blob-inspector',
            'corda-tools-explorer',
            'corda-tools-network-bootstrapper',
            'corda-tools-cliutils',
            'corda-common-configuration-parsing',
            'corda-common-validation',
            'corda-common-logging',
            'corda-tools-network-builder',
            'corda-tools-checkpoint-agent'
    ]
    license {
        name = 'Apache-2.0'
        url = 'https://www.apache.org/licenses/LICENSE-2.0'
        distribution = 'repo'
    }
    developer {
        id = 'R3'
        name = 'R3'
        email = 'dev@corda.net'
    }
}

// Build a ZIP of all JARs required to compile the Cordapp template
// Note: corda.jar is used at runtime so no runtime ZIP is necessary.
// Resulting ZIP can be found in "build/distributions"
task buildCordappDependenciesZip(type: Zip) {
    baseName 'corda-deps'
    from configurations.runtime
    from configurations.compile
    from configurations.testCompile
    from buildscript.configurations.classpath
    from 'node/capsule/NOTICE' // CDDL notice
    duplicatesStrategy = DuplicatesStrategy.EXCLUDE
}

artifactory {
    publish {
        contextUrl = artifactory_contextUrl
        repository {
            repoKey = 'corda-dev'
            username = System.getenv('CORDA_ARTIFACTORY_USERNAME')
            password = System.getenv('CORDA_ARTIFACTORY_PASSWORD')
        }

        defaults {
            // Root project applies the plugin (for this block) but does not need to be published
            if (project != rootProject) {
                publications(project.extensions.publish.name())
            }
        }
    }
}

tasks.register('generateApi', net.corda.plugins.apiscanner.GenerateApi) {
    baseName = "api-corda"
}

// This exists to reduce CI build time when the envvar is set (can save up to 40 minutes)
if (file('corda-docs-only-build').exists() || (System.getenv('CORDA_DOCS_ONLY_BUILD') != null)) {
    if (file('corda-docs-only-build').exists()) {
        logger.info("Tests are disabled due to presence of file 'corda-docs-only-build' in the project root")
    } else {
        logger.info("Tests are disabled due to the presence of envvar CORDA_DOCS_ONLY_BUILD")
    }

    allprojects {
        test {
            exclude '*/**'
        }

        it.afterEvaluate {
            if (it.tasks.findByName("integrationTest") != null) {
                integrationTest {
                    exclude '*/**'
                }
            }
        }

        it.afterEvaluate {
            if (it.tasks.findByName("smokeTest") != null) {
                smokeTest {
                    exclude '*/**'
                }
            }
        }
    }
}

wrapper {
    gradleVersion = '5.6.4'
    distributionType = Wrapper.DistributionType.ALL
}

buildScan {
    termsOfServiceUrl = 'https://gradle.com/terms-of-service'
    termsOfServiceAgree = 'yes'
}

distributedTesting {
    profilesURL = 'https://raw.githubusercontent.com/corda/infrastructure-profiles/master'

    parallelTestGroups {
        allParallelIntegrationTest {
            testGroups 'integrationTest'
            profile 'generalPurpose.yml'
            podLogLevel PodLogLevel.INFO
            distribution DistributeTestsBy.METHOD
        }
        allParallelUnitTest {
            podLogLevel PodLogLevel.INFO
            testGroups 'test'
            profile 'generalPurpose.yml'
            distribution DistributeTestsBy.CLASS
        }
        allParallelUnitAndIntegrationTest {
            testGroups 'test', 'integrationTest'
            profile 'generalPurpose.yml'
            distribution DistributeTestsBy.METHOD
        }
        allParallelSmokeTest {
            testGroups 'smokeTest'
            profile 'regression.yml'
            distribution DistributeTestsBy.METHOD
        }
        allParallelSlowIntegrationTest {
            testGroups 'slowIntegrationTest'
            profile 'regression.yml'
            distribution DistributeTestsBy.METHOD
        }
    }

    ignoredTests = [
        ':core-deterministic:testing:data:test'
    ]
